/*$6*/


#pragma once
#include "PseudoRandomGenerator.h"
#include <vector>
class   BasylPseudoAdaptor
{
public:
    BasylPseudoAdaptor();
    ~                           BasylPseudoAdaptor();

    //Swaps the two positions in the generator. By default, it justs swaps them. You can make this more creative.
    virtual void                OddSwap(std::vector < unsigned __int64 > &gen,
                                        int pos1, int pos2);

    //Shuffles things around to enhance the generation scheme. By default it does nothing.
    virtual void                Shuffle(std::vector < unsigned __int64 > &gen,
                                        int round);

    //Allows you to add steps in the recycling step of the key.
    virtual void                Recycle(std::vector < unsigned __int64 > &gen);

    //Allows you to easily change out seed functions.
    virtual unsigned __int64    SeedFunction(unsigned __int64 pos,
                                             unsigned __int64 seed);
};
