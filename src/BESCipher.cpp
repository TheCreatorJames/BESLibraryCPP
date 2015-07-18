#include "BESCipher.h"
#include <iostream>

BESCipher::BESCipher() : keyGen((IBasylKeyGenerator*)(new BasylKeyGenerator(""))), Cipher(new byte[256]()), CipherB(new byte[256]())
{
	//Init();
}

BESCipher::BESCipher(IBasylKeyGenerator* gen) : keyGen(gen), Cipher(new byte[256]()), CipherB(new byte[256]())
{

}

BESCipher::BESCipher(const BESCipher& cipher) : keyGen(cipher.keyGen), Cipher(new byte[256]()), CipherB(new byte[256]())
{
	for (int i = 0; i < 256; i++)
	{
		Cipher[i] = cipher.Cipher[i];
		CipherB[i] = cipher.CipherB[i];
	}
}

BESCipher::~BESCipher()
{
	delete[] Cipher;
	delete[] CipherB;

}

IBasylKeyGenerator* BESCipher::KeyGen()
{
	return keyGen;
}

void BESCipher::Refresh()
{
	
	for (int i = 0; i < 256; i++)
	{
		CipherB[Cipher[i]] = (byte)i;
	}
}


void BESCipher::Init()
{
	for (int i = 0; i < 256; i++)
	{
		Cipher[i] = (byte)i;
	}
	Shuffle(10);


	for (int i = 0; i < 256; i++)
	{
		std::cout << to_string(Cipher[i]) << endl;
	}
}


//Shuffles everything around in the array. This is mainly used to randomize the starting positions.
//you may specify the number of times
void BESCipher::Shuffle(int times = 10)
{
	byte v;
	byte pos;
	for (int j = 0; j < times; j++)
	for (int i = 0; i < 256; i++)
	{
		pos = keyGen->GetRandomByte();

		swap(Cipher[i], Cipher[pos]);
	}
	Refresh();
}

//shuffles bytes at the given position in the cipher array.
void BESCipher::ShufflePosition(int pos)
{
	byte pos2 = keyGen->GetRandomByte();
	
	//CipherB[Cipher[pos2]] = pos;
	//CipherB[Cipher[pos]] = pos2;
	swap(CipherB[Cipher[pos2]], CipherB[Cipher[pos]]);

	/*
	byte b = Cipher[pos2];
	Cipher[pos2] = Cipher[pos];
	Cipher[pos] = b; */
	swap(Cipher[pos2], Cipher[pos]);
}


//Encrypt Right//
//Encrypts bytes "to the right". This means that to reverse the process, you need to "encrypt" left.
void BESCipher::EncryptRight(byte& b)
{
	b = Cipher[b];
	ShufflePosition(CipherB[b]);
}

void BESCipher::EncryptRight(byte b[], int size)
{
	for (int i = 0; i < size; i++)
	{
		EncryptRight(b[i]);
	}
}

void BESCipher::EncryptRight(char& b)
{
	EncryptRight((byte&)b);
}

void BESCipher::EncryptRight(char b[], int size)
{
	EncryptRight((byte *)b, size);
}

void BESCipher::EncryptRight(string& b)
{
	EncryptRight((byte*)b.c_str(), b.size());
}
//End Encrypt Right//

//Encrypt Left//
//Encrypts "to the left". To reverse this process, "encrypt" to the right.
void BESCipher::EncryptLeft(byte& b)
{
	b = CipherB[b];
	ShufflePosition(b);
}

void BESCipher::EncryptLeft(byte b[] , int size)
{
	for (int i = 0; i < size; i++)
	{
		EncryptLeft(b[i]);
	}
}

void BESCipher::EncryptLeft(char& b)
{
	EncryptLeft((byte&)b);
}

void BESCipher::EncryptLeft(char b[], int size)
{
	EncryptLeft((byte*)b, size);
}

void BESCipher::EncryptLeft(string& b)
{
	EncryptLeft((byte*)b.c_str(), b.size());
}
//End Encrypt Left//