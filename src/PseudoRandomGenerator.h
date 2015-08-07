/*$6*/


#pragma once
#include <vector>
#include <string>
#include "BasylArray.h"
#include "BasylPseudoAdaptor.h"
#include <memory>

class           BasylPseudoAdaptor;
using namespace std;
class           PseudoRandomGenerator
{
private:
    vector<unsigned __int64>            Generation;
    int                                 rounds,
                                        leftoff,
                                        position;
    bool                                additionalSet,
                                        shaSet;
    string                              recycleKey;
    BasylArray<unsigned __int8>         sha,
                                        additionalKey;
    std::shared_ptr<BasylPseudoAdaptor> adaptor;

    void                                Generate(string, int);

    void                                Recycle(bool);
    void                                Cipher(int);
    void                                Cipher();
    void                                CipherB();
    void                                ResizeGeneration(int);

    unsigned __int64                    SeedFunction(unsigned __int64,
                                                     unsigned __int64);
public:
    PseudoRandomGenerator();
    PseudoRandomGenerator(int);
    PseudoRandomGenerator(int, string);
    PseudoRandomGenerator(int, string, int);
    PseudoRandomGenerator (int, string, int, std::shared_ptr<BasylPseudoAdaptor> );
    ~               PseudoRandomGenerator();

    void            SetSHA(BasylArray<unsigned __int8> );
    void            SetAdditional(BasylArray<unsigned __int8> );
    void            SetRecycleKey(string);

    void            SetLeftoff(int);
    void            ExpandKey(int);

    void            Recycle();

    unsigned __int8 GetRandomByte();

    void            FillBytes(unsigned __int8[], int);
    void            FillBytes(char[], int);

    void            Drop();
};
