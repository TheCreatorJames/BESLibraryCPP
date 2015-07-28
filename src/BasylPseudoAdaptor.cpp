#include "BasylPseudoAdaptor.h"



BasylPseudoAdaptor::BasylPseudoAdaptor()
{
}


BasylPseudoAdaptor::~BasylPseudoAdaptor()
{
}

void BasylPseudoAdaptor::OddSwap(vector<unsigned __int64>& gen, int pos1, int pos2)
{
	unsigned __int64 temp = gen[pos1];
	gen[pos1] = gen[pos2];
	gen[pos2] = temp;
}

void BasylPseudoAdaptor::Shuffle(vector<unsigned __int64>& gen, int round)
{

}

void BasylPseudoAdaptor::Recycle(vector<unsigned __int64>& gen)
{
}

unsigned __int64 BasylPseudoAdaptor::SeedFunction(unsigned __int64 pos, unsigned __int64 seed)
{
	return pos * pos + 2 * pos + pos * pos * pos + seed * pos + seed;
}
