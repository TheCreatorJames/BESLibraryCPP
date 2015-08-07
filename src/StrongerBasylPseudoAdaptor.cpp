/*$6*/


#include "StrongerBasylPseudoAdaptor.h"

//finds a location to swap pieces between indirectly, and at variant depth.
int StrongerBasylPseudoAdaptor::Layers(vector<unsigned __int64> &gen,
                                       unsigned __int64 current,
                                       unsigned __int64 depth)
{
    if (depth <= 0)
    {
        return (int) (current % (unsigned __int64) gen.size());
    }

    return Layers(gen, gen[(int) (current % (unsigned __int64) gen.size())],
                  depth - 1);
}

StrongerBasylPseudoAdaptor::StrongerBasylPseudoAdaptor()
{
}

StrongerBasylPseudoAdaptor::~StrongerBasylPseudoAdaptor()
{
}

void StrongerBasylPseudoAdaptor::Shuffle(vector<unsigned __int64> &gen, int round)
{
    if (round % 100 == 2)
    {
        for (int i = 0; i < gen.size(); i++)
        {
            unsigned __int64    temporary = gen[i];
            unsigned __int64    otherPosition = Layers(gen, gen[i],
                                                       ((temporary << 2) ^ (temporary >> 2)) % 8 + 1);
            OddSwap(gen, i, otherPosition);
        }
    }
}
