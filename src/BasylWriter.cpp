#include "BasylWriter.h"
#include <string>
#include <vector>
#include <ctime>

//creates a writer with shared resources with the reader.
BasylWriter::BasylWriter(ostream* stream, BasylReader reader)
{
	output = stream;
	keyGen = reader.keyGen;
}



BasylWriter::BasylWriter(ostream * stream, const BasylKeyGenerator& gen, bool exp)
{
	output = stream;
	keyGen = make_shared<BasylKeyGenerator>(gen);
	if (exp) //exports it
	{
		for (int i = 0; i < keyGen->Hash().size(); i++)
		{
			(*output) << (byte)keyGen->Hash()[i];
		}

		for (int i = 0; i < keyGen->Key2Random().size(); i++)
			(*output) << (byte)keyGen->Key2Random()[i];


		BasylArray<byte> enc = keyGen->EncryptedKey1Random();
		for (int i = 0; i < enc.size(); i++)
			(*output) << (byte)enc[i];
	}
}

BasylWriter::~BasylWriter()
{
}


BasylWriter& BasylWriter::operator<<(byte byte)
{
	byte ^= keyGen->GetRandomByte();
	*output << byte;
	return *this;
}


BasylWriter& BasylWriter::operator<<(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		str[i] ^= keyGen->GetRandomByte();
	}
	(*output).write(str.c_str(), str.size());
	return *this;
}

void BasylWriter::write(string str)
{
	*this << str;
}

void BasylWriter::write(byte bytes[],int size)
{
	for (int i = 0; i < size; i++)
	{
		bytes[i] ^= keyGen->GetRandomByte();
	
	}
	(*output).write((char*)bytes, size);
}

void BasylWriter::write(char bytes[], int size)
{
	write((byte*)bytes, size);
}

void BasylWriter::write(byte b)
{
	b ^= keyGen->GetRandomByte();
	(*output) << b;

}

void BasylWriter::write(char b)
{
	write((byte)b);
}
