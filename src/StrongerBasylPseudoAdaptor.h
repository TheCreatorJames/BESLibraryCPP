/*$6*/


#pragma once
#include "BasylPseudoAdaptor.h"
class StrongerBasylPseudoAdaptor :
    public BasylPseudoAdaptor
{
private:
    int Layers(vector<unsigned __int64> &gen, unsigned __int64 current,
               unsigned __int64 depth);
public:
    StrongerBasylPseudoAdaptor();
    ~               StrongerBasylPseudoAdaptor();

    virtual void    Shuffle(vector<unsigned __int64> &gen, int round);
};
