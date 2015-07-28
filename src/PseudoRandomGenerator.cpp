#include "PseudoRandomGenerator.h"
#include <ctime>

//I couldn't figure out how to do the time string thing. This will do.
string GetRandomness()
{
	std::srand(std::time(0));
	rand();
	return to_string(rand() * rand() + rand());
}

PseudoRandomGenerator::PseudoRandomGenerator() : PseudoRandomGenerator(16*1024)
{
}

PseudoRandomGenerator::PseudoRandomGenerator(int size) : PseudoRandomGenerator(size, GetRandomness())
{

}

PseudoRandomGenerator::PseudoRandomGenerator(int size, string pass) : PseudoRandomGenerator(size, pass, 400)
{
}


PseudoRandomGenerator::PseudoRandomGenerator(int size, string pass, int rounds) : PseudoRandomGenerator(size, pass, rounds, make_shared<BasylPseudoAdaptor>())
{
}

PseudoRandomGenerator::PseudoRandomGenerator(int size, string pass, int rounds, shared_ptr<BasylPseudoAdaptor> adaptor) : rounds(rounds), recycleKey(""), position(0), adaptor(adaptor)
{
	ResizeGeneration(size);
	Generate(pass, size);	
}

PseudoRandomGenerator::~PseudoRandomGenerator()
{
}


void PseudoRandomGenerator::Generate(string pass, int size)
{
	if (size == 0) return; 

	unsigned __int64 seed = 1;

	//char[] keyN = key.ToCharArray();
	Generation[0] = size;

	//Seed the array with the password, and also make the seed. I need to really convert to UTF-16. This should work though.
	for (int i = 0; i < pass.length(); i++)
	{
		Generation[i + 1] += pass[i];
		seed += pass[i];
	}

	//Seed the data with generated values from a seed function.
	for (unsigned __int32 i = 0; i < size; i++)
	{
		Generation[(int)i] += (SeedFunction(i, seed));
	}

	//Cipher it.
	for (int i = 0; i < rounds; i++)
	{
		adaptor->Shuffle(Generation, i);

		if (i % 2 == 0)
			Cipher();
		else
			CipherB();
	}
}

unsigned __int64 PseudoRandomGenerator::SeedFunction(unsigned __int64 pos, unsigned __int64 seed)
{
	return adaptor->SeedFunction(pos, seed);
	//return pos * pos + 2 * pos + pos * pos * pos + seed * pos + seed;
}

void PseudoRandomGenerator::Cipher(int begin)
{
	for (int i = begin; i < Generation.size(); i++)
	{
		Generation[i] += Generation[i - 1];
		if (Generation[i] > 400000000) Generation[i] %= 913131;
	}
}

/// <summary>
/// This method adds previous numbers in the array, and it gets moduloed and mutated
/// through waterfalling. The process is not reversible, and generates high entropy.
/// </summary>
void PseudoRandomGenerator::Cipher()
{
	Cipher(1);
}

void PseudoRandomGenerator::CipherB()
{
	for (int i = Generation.size() - 2; i >= 0; i--)
	{
		Generation[i] += Generation[i + 1];

		if (Generation[i] > 400000000) Generation[i] %= 913131;
	}
}


void PseudoRandomGenerator::Recycle()
{
	Recycle(false);
}

void PseudoRandomGenerator::Recycle(bool enhanced)
{
	
	if (enhanced)
	{
		Cipher(position);
	}
	else
	{
		//Add the recycle key to the Generation Scheme.
		for (int i = 0; i < recycleKey.length(); i++)
		{

			Generation[i] += recycleKey[i];
		}

		//Add the SHA to the Generation Scheme
		if (shaSet)
		{
			for (int i = 0; i < sha.size(); i++)
			{

				Generation[i] += sha[i];

			}

		}

		//add the seed key to the generation scheme.
		if (additionalSet)
		{
			for (int i = 0; i < additionalKey.size(); i++)
			{
				Generation[i] += additionalKey[i];
			}
		}
	}



	for (int i = 0; i < 1; i++) //could be adjusted
	{
		
		if (!(enhanced && i == 0))
		{
			Cipher();
		}

		CipherB();
	}

	adaptor->Recycle(Generation);
	position = 0;
	//turn++;
}

void PseudoRandomGenerator::ResizeGeneration(int size)
{
	while (Generation.size() < size)
	{
		Generation.push_back(0);
	}
}


void  PseudoRandomGenerator::SetSHA(BasylArray<unsigned __int8> sha)
{
	this->sha = BasylArray<unsigned __int8>(sha);
	this->shaSet = true;
}

void  PseudoRandomGenerator::SetAdditional(BasylArray<unsigned __int8> additional)
{
	this->additionalKey = BasylArray<unsigned __int8>(additional);
	this->additionalSet = true;
}

void  PseudoRandomGenerator::SetRecycleKey(string key)
{
	this->recycleKey = key;
}

void  PseudoRandomGenerator::SetLeftoff(int leftoff)
{
	this->leftoff = leftoff;
}


void  PseudoRandomGenerator::ExpandKey(int times)
{

	if (times < 1) return; //bug fix

	vector<unsigned __int64> expander;

	for (unsigned int k = 0; k < times; k++)
	{
		Generation[0] += times;
		Generation[2] += k;
		Generation[3] += times + k + (unsigned __int64)expander.size();
		Generation[4] += (unsigned __int64)Generation.size();

		if (k % 2 == 0)
			Cipher();
		else
			CipherB();

		for (int i = 0; i < Generation.size(); i++)
		{
			expander.push_back(Generation[i]);
		}

	}

	Generation = expander;
}

unsigned __int8 PseudoRandomGenerator::GetRandomByte()
{
	if ((position + leftoff) >= Generation.size())
	{
			Recycle(true);
	}

	unsigned __int8 r = (unsigned __int8)(Generation[position] % 256);
	Generation[position] += r;


	if (position != 0)
	{
		Generation[position] += Generation[position - 1];
		if (Generation[position] > 400000000) Generation[position] %= 913131;
	}

	if (shaSet && position < sha.size())
	{
		Generation[position] += sha[position];
	}

	if (additionalSet && position < additionalKey.size())
	{
		Generation[position] += additionalKey[position];
	}

	if (position < recycleKey.length())
	{
		Generation[position] += recycleKey[position];
	}

	position++;
	return r;

}

void  PseudoRandomGenerator::FillBytes(unsigned __int8 bytes[], int size)
{
	for (int i = 0; i < size; i++)
	{
		bytes[i] = GetRandomByte();
	}
}

void  PseudoRandomGenerator::FillBytes(char bytes[], int size)
{
	for (int i = 0; i < size; i++)
	{
		bytes[i] = GetRandomByte();
	}
}

void  PseudoRandomGenerator::Drop()
{
	Generation.clear();
}