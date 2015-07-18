#include <iostream>
#include <vector>
#include <string>
#include "BasylFileEncryption.h"
#include "BESCipher.h"
#include "BasylArray.h"
using namespace std;



void clear()
{
	cin.ignore(UINT64_MAX);
}

void pause()
{
	string w; 
	getline(cin, w);
}


int main(int argC, const char * args)
{
	/*
	BasylFileEncryption::CipherMode(true);
	BasylFileEncryption::Encrypt("Rand.mp4", "James");
	BasylFileEncryption::Decrypt("Rand.mp4.bes", "Rand.mp4", "James");
	*/
	/*
	BasylKeyGenerator bed("Hello World");
	bed.ForceRecycle();
	bed.Key2().Recycle();
	bed.Key1().GetRandomByte();
	//Woot.
	BESCipher cipher(bed);

	unsigned int i = 0;
	while (true)
	{
		char n = (char)(i % 256);
		cipher.EncryptLeft(n);
		cout << n;
	}
	*/

	pause();
}
