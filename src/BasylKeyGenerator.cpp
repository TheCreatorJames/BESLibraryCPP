#include "BasylKeyGenerator.h"
#include <ctime>

BasylKeyGenerator::BasylKeyGenerator() : _Key1(0), _Key2(0)
{
}


BasylKeyGenerator::BasylKeyGenerator(const BasylKeyGenerator& b) : _Key1(b._Key1), _Key2(b._Key2), key1Random(b.key1Random), key2Random(b.key2Random), hash(b.hash)
{

}

BasylKeyGenerator::BasylKeyGenerator(string pass, ifstream*source) : _Key1(0), _Key2(0)
{
	char hash[32];
	(*source).read(hash, 32);


	char Key2Random[4];
	(*source).read(Key2Random, 4);

	char Key1Random[4]; //:)
	(*source).read(Key1Random, 4);


	Init(pass, INITIAL, ROUNDS, LEFTOFF, EXPANSION, ADDITIONALKEY, BasylArray<byte>((byte*)hash, 32), BasylArray<byte>((byte*)Key1Random, 4), BasylArray<byte>((byte*)Key2Random, 4), true);
}


BasylKeyGenerator::BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, ifstream*source) : _Key1(0), _Key2(0)
{

	char hash[32];
	(*source).read(hash, 32);


	char Key2Random[4];
	(*source).read(Key2Random, 4);

	char Key1Random[4]; //:)
	(*source).read(Key1Random, 4);

	Init(pass, initial, rounds, leftoff, expansion, additionalKey, BasylArray<byte>((byte*)hash, 32), BasylArray<byte>((byte*)Key1Random,4), BasylArray<byte>((byte*)Key2Random,4), true);


}

BasylKeyGenerator::~BasylKeyGenerator() 
{

}

BasylKeyGenerator::BasylKeyGenerator(string pass) : _Key1(0), _Key2(0)
{
	Init(pass, INITIAL, ROUNDS, LEFTOFF, EXPANSION, ADDITIONALKEY);
}

BasylKeyGenerator::BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey) : _Key1(0), _Key2(0)
{
	Init(pass, initial, rounds, leftoff, expansion, additionalKey);
}

BasylKeyGenerator::BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted) : _Key1(0), _Key2(0)
{
	Init(pass, initial, rounds, leftoff, expansion, additionalKey, hash, key1, key2, encrypted);
}

BasylKeyGenerator::BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted, shared_ptr<BasylPseudoAdaptor> adaptor) : _Key1(0), _Key2(0) 
{
	Init(pass, initial, rounds, leftoff, expansion, additionalKey, hash, key1, key2, encrypted, adaptor);
}


static bool randomize;
//I'll need to add SHA in later on. This is a security issue.
BasylArray<byte> GetRandomizedHash()
{
	if (!randomize)
	{
		std::srand(std::time(0));
		rand(); rand(); rand();
		rand(); rand(); rand();
		rand(); rand(); rand();
		randomize = true;
	}

	BasylArray<byte> res(32);
	int count = 0;
	while (res.size() < 32)
	{
		rand();
		//res.push_back(rand());
		res[count++] = (byte)rand();
	}
	return res;
}

//I need to add in CryptGenRandom or something.
void GetRandom(byte* res, int size)
{
	for (int i = 0; i < size; i++)
	{
		res[i] = (byte)rand();
	}

}

void BasylKeyGenerator::Init(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey)
{
	byte n[4], q[4];
	GetRandom(n, 4);
	GetRandom(q, 4);
	Init(pass, initial, rounds, leftoff, expansion, additionalKey, GetRandomizedHash(), BasylArray<byte>(n, 4), BasylArray<byte>(q, 4), false);
}

void BasylKeyGenerator::Init(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted)
{
	Init(pass, initial, rounds, leftoff, expansion, additionalKey, hash, key1, key2, encrypted, make_shared<BasylPseudoAdaptor>());
}

void BasylKeyGenerator::Init(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted, shared_ptr<BasylPseudoAdaptor> adaptor)
{
	_Key1 = PseudoRandomGenerator(initial, pass, rounds, adaptor);
	_Key2 = PseudoRandomGenerator(1024 * 40, pass, 400, adaptor);

	//Set the left off
	_Key1.SetLeftoff(leftoff);
	_Key2.SetLeftoff(80);


	//Set String Recycle Key
	_Key1.SetRecycleKey(additionalKey);
	_Key2.SetRecycleKey(additionalKey);

	//Expand the Keys
	_Key1.ExpandKey(expansion);
	_Key2.ExpandKey(5);

	key1Random = key1;
	key2Random = key2;

	//Add Randomness
	_Key2.SetAdditional(key2);


	//Set Hash
	_Key1.SetSHA(hash);
	_Key2.SetSHA(hash);
	this->hash = hash;

	//Recycle the Second Key.
	_Key2.Recycle();


	if (encrypted)
	{
		for (int i = 0; i < key1.size(); i++)
		{
			key1Random[i] ^= _Key2.GetRandomByte();
		}
	}
	_Key1.SetAdditional(key1Random);
	_Key1.Recycle();
}

byte BasylKeyGenerator::GetRandomByte()
{
	return _Key1.GetRandomByte() ^ _Key2.GetRandomByte();
}

void BasylKeyGenerator::Encrypt(__int8& b)
{
	b ^= GetRandomByte();
}

void BasylKeyGenerator::Encrypt(byte& b)
{
	b ^= GetRandomByte();
}

void BasylKeyGenerator::Encrypt(__int8 b[], int size)
{
	Encrypt((byte*)b, size);
}

void BasylKeyGenerator::Encrypt(byte b[], int size)
{
	for (int i = 0; i < size; i++)
	{
		b[i] ^= GetRandomByte();
	}
}

void BasylKeyGenerator::Encrypt(string x)
{
	Encrypt((byte*)x.c_str(), x.size());
}

BasylArray<byte> BasylKeyGenerator::EncryptedKey1Random()
{
	BasylArray<byte> result(key1Random);

	for (int i = 0; i < result.size(); i++)
	{
		result[i] ^= _Key2.GetRandomByte();
	}

	return result;
}

void BasylKeyGenerator::ForceRecycle()
{
	_Key1.Recycle();
	_Key2.Recycle();
}

//Gets Key 1.
PseudoRandomGenerator& BasylKeyGenerator::Key1()
{
	return _Key1;
}

//Gets Key 2.
PseudoRandomGenerator& BasylKeyGenerator::Key2()
{
	return _Key2;
}

BasylArray<byte> BasylKeyGenerator::Hash()
{
	return BasylArray<byte>(hash);
}

BasylArray<byte> BasylKeyGenerator::Key1Random()
{
	return BasylArray<byte>(key1Random);
}

BasylArray<byte> BasylKeyGenerator::Key2Random()
{
	return BasylArray<byte>(key2Random);
}
