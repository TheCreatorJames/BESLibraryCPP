#pragma once
#include "BasylKeyGenerator.h"

class BESCipher
{
private:
	IBasylKeyGenerator* keyGen;
	byte* Cipher, *CipherB;
	void Refresh();
	BESCipher();
public:
	
	/*BESCipher(string);
	BESCipher(string, int, int, int, int, string);
	BESCipher(string, int, int, int, int, string, byte* Key1Random, byte* Key2Random, int keySize, vector<byte> hash);
	*/

	BESCipher(IBasylKeyGenerator* gen);
	BESCipher(const BESCipher& cipher);
	~BESCipher();

	IBasylKeyGenerator* KeyGen();

	void Init();

	void Shuffle(int);
	void ShufflePosition(int);


	void EncryptRight(string&);
	void EncryptRight(byte&);
	void EncryptRight(byte[], int);
	void EncryptRight(char&);
	void EncryptRight(char[], int);


	void EncryptLeft(string&);
	void EncryptLeft(byte&);
	void EncryptLeft(byte[], int);
	void EncryptLeft(char&);
	void EncryptLeft(char[], int);
};

