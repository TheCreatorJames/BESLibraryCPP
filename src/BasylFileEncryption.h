#pragma once
#include <string>
#include <fstream>
#include "BasylReader.h"
#include "BasylWriter.h"
#include "BESCipher.h"
class BasylFileEncryption
{
private:
	BasylFileEncryption();
	~BasylFileEncryption();
	static bool cipherMode;
	static void Encrypt(ifstream& in, ofstream& out, BasylKeyGenerator& keyGen)
	{
		if (in.good() && out.good())
		{
			BasylWriter writer(&out, keyGen, true);

			BESCipher* cipher = nullptr;


			if (cipherMode)
			{
				keyGen.EncryptedKey1Random();
				cipher = new BESCipher((IBasylKeyGenerator*)&keyGen);
				cipher->Init();
			}


			int orig = in.tellg();
			in.seekg(0, SEEK_END);
			int size = (int)in.tellg() - orig;
			in.seekg(orig);

			int pos = orig;
			char buffer[512 * 1024];
			while (pos + 512 * 1024 < size)
			{
				in.read(buffer, 512 * 1024);
				//writer.write(buffer, 512 * 1024);
				if (!cipherMode)
				writer.write(buffer, 512 * 1024);
				else
				{
					cipher->EncryptRight(buffer, 512 * 1024);
					out.write(buffer, 512 * 1024);
				}
				//out.flush();
				pos += 512 * 1024;
			}

			in.read(buffer, (size) % (512 * 1024));

			if (!cipherMode)
			writer.write(buffer, (size) % (512 * 1024));
			else
			{
				cipher->EncryptRight(buffer, (size) % (512 * 1024));
				out.write(buffer, (size) % (512 * 1024));
				delete cipher;
			}



			//writer.write(buffer, (size) % (512 * 1024));
		}
		in.close();
		out.close();
	}

	static void Decrypt(ifstream& in, ofstream& out, BasylKeyGenerator& gen)
	{
		if (in.good() && out.good())
		{
			BasylReader reader(&in, gen);

			BESCipher* cipher = nullptr;

			if (cipherMode)
			{
				cipher = new BESCipher((IBasylKeyGenerator*)&gen);
				cipher->Init();
			}


			int orig = in.tellg();
			in.seekg(0, SEEK_END);
			int size = (int)in.tellg() - orig;
			in.seekg(orig);

			int pos = orig;
			char buffer[512 * 1024];
			while (pos + 512 * 1024 < size)
			{
				
				if (cipherMode)
				{
					in.read(buffer, 512 * 1024);
					cipher->EncryptLeft(buffer, 512 * 1024);
				}
				else
				reader.read(buffer, 512 * 1024);
								
				
				
				out.write(buffer, 512 * 1024);
				pos += 512 * 1024;
			}


			if (cipherMode)
			{
				in.read(buffer, (size) % (512 * 1024));
				cipher->EncryptLeft(buffer, (size) % (512 * 1024));
				delete cipher;
			}
			else
			reader.read(buffer, (size) % (512 * 1024));
			out.write(buffer, (size) % (512 * 1024));

			in.close();
			out.close();
		}
	}


public:

	static bool CipherMode()
	{
		return cipherMode;
	}

	static bool CipherMode(bool n)
	{
		return (cipherMode = n);
	}

	//Encrypt Files
	static void Encrypt(string fileName, string outputName, string pass, int initial, int rounds, int leftoff, int expansion, string additional)
	{
		ifstream in(fileName, ios::binary);
		ofstream out(outputName, ios::binary);
		Encrypt(in, out, BasylKeyGenerator(pass, initial, rounds, leftoff, expansion, additional));
	}
	
	static void Encrypt(string fileName, string pass, int initial, int rounds, int leftoff, int expansion, string additional)
	{
		Encrypt(fileName, fileName + ".bes", pass, initial, rounds, leftoff, expansion, additional);
	}

	static void Encrypt(string fileName, string outputName, string pass)
	{
		ifstream in(fileName, ios::binary);
		ofstream out(outputName, ios::binary);
		Encrypt(in, out, BasylKeyGenerator(pass));
	}
	
	static void Encrypt(string fileName, string pass)
	{
		Encrypt(fileName, fileName + ".bes", pass);
	}

	//Decrypt Files
	static void Decrypt(string fileName, string outputName, string pass, int initial, int rounds, int leftoff, int expansion, string additional)
	{

		ifstream in(fileName, ios::binary);
		ofstream out(outputName, ios::binary);
		
		Decrypt(in, out, BasylKeyGenerator(pass, initial, rounds, leftoff, expansion, additional, &in));
	}

	static void Decrypt(string fileName, string outputName, string pass)
	{
		ifstream in(fileName, ios::binary);
		ofstream out(outputName, ios::binary);
		Decrypt(in, out, BasylKeyGenerator(pass, &in));
	}

	static void Decrypt(string fileName, string pass, int initial, int rounds, int leftoff, int expansion, string additional)
	{
		Decrypt(fileName, fileName.substr(0, fileName.find_last_of('.')), pass, initial, leftoff, rounds, expansion, additional);
	}

	static void Decrypt(string fileName, string pass)
	{
		Decrypt(fileName, fileName.substr(0, fileName.find_last_of('.')), pass);
	}
};

