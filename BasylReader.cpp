#include "BasylReader.h"


BasylReader::BasylReader(istream* stream, const BasylKeyGenerator& gen)
{
	input = stream;
	keyGen = make_shared<BasylKeyGenerator>(gen);
}

//creates a reader with shared resources with the writer.
BasylReader::BasylReader(istream* stream, BasylWriter writer)
{
	input = stream;
	keyGen = writer.keyGen;
}

BasylReader::~BasylReader()
{
}

//Gets the Key Generator.
shared_ptr<BasylKeyGenerator> BasylReader::KeyGen()
{
	return keyGen;
}


void BasylReader::read(char buffer[], int size)
{
	(*input).read(buffer, size);

	for (int i = 0; i < size; i++)
	{
		buffer[i] ^= keyGen->GetRandomByte();
	}
}


byte BasylReader::get()
{
	return read();
}

byte BasylReader::read()
{
	byte let = (*input).get();
	let ^= keyGen->GetRandomByte();
	return let;
}

byte BasylReader::readUnencrypted()
{
	return (*input).get();
}

//reads in an unencrypted byte.
byte BasylReader::getUnencrypted()
{
	return readUnencrypted();
}

//reads in an unencrypted byte array to the buffer.
void BasylReader::readUnencrypted(char buffer[], int size)
{
	(*input).read(buffer, size);
}

void BasylReader::operator>>(byte &let)
{
	let = read();
}