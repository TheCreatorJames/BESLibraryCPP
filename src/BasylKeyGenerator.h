#pragma once
#include "PseudoRandomGenerator.h"
#include <fstream>
#include "BasylArray.h"
#include "IBasylKeyGenerator.h";


//Default Settings
const int INITIAL = 131072;
const int ROUNDS = 200;
const int LEFTOFF = 1200;
const int EXPANSION = 120;
const string ADDITIONALKEY = "ABCD";
//End Default Settings

class BasylKeyGenerator : IBasylKeyGenerator
{
private:
	BasylKeyGenerator();
	PseudoRandomGenerator _Key1, _Key2;
	BasylArray<byte> key1Random, key2Random, hash;

	//For Chaining Constructors.
	void Init(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey);
	void Init(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted);
public:
	BasylKeyGenerator(string pass);
	BasylKeyGenerator(string pass, ifstream*source);
	BasylKeyGenerator(const BasylKeyGenerator& b);
	BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey);
	BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, ifstream*source);
	BasylKeyGenerator(string pass, int initial, int rounds, int leftoff, int expansion, string additionalKey, BasylArray<byte> hash, BasylArray<byte> key1, BasylArray<byte> key2, bool encrypted);
	~BasylKeyGenerator();

	byte GetRandomByte();

	BasylArray<byte> EncryptedKey1Random();

	void Encrypt(__int8&);
	void Encrypt(byte&);

	void Encrypt(__int8[], int size);
	void Encrypt(byte[], int size);
	void Encrypt(string);

	BasylArray<byte> Hash();
	BasylArray<byte> Key1Random();
	BasylArray<byte> Key2Random();

	void ForceRecycle();

	PseudoRandomGenerator& Key1();
	PseudoRandomGenerator& Key2();
};
