#pragma once
#include "PseudoRandomGenerator.h"
#include "BasylReader.h"
#include "BasylKeyGenerator.h"
#include <memory>

typedef unsigned __int8 byte;
class BasylWriter
{
friend class BasylReader;
private:
	shared_ptr<BasylKeyGenerator> keyGen;
	ostream * output;
public:

	BasylWriter(ostream*, BasylReader);
	BasylWriter(ostream*, const BasylKeyGenerator& gen, bool exp);
	~BasylWriter();
	
	BasylWriter& operator<<(unsigned __int8);
	BasylWriter& operator<<(string);

	void write(unsigned __int8[], int size);
	void write(char[], int size);
	void write(byte);
	void write(char);
	void write(string);
};

