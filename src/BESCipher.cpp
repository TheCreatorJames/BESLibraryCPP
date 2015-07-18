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


void BESCipher::Shuffle(int times)
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