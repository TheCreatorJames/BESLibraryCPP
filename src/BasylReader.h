/*$6*/


#pragma once
#include "PseudoRandomGenerator.h"
#include "BasylWriter.h"
#include "BasylKeyGenerator.h"
#include <memory>
typedef unsigned __int8 byte;
class                   BasylReader
{
    friend class    BasylWriter;
private:
    istream                         *input;
    shared_ptr<BasylKeyGenerator>   keyGen;
public:
    BasylReader(istream *stream, BasylWriter writer);
    BasylReader(istream *stream, const BasylKeyGenerator &gen);
    ~                               BasylReader();

    //Gets the Key Generator.
    shared_ptr<BasylKeyGenerator>   KeyGen();

    //reads in data to the buffer.
    void                            read(char buffer[], int);

    //reads in a byte (decrypted).
    unsigned __int8                 read();

    //reads in a byte (decrypted).
    unsigned __int8                 get();

    //reads in a byte (decrypted).
    void operator                   >>(unsigned __int8 &);

    //reads in an unencrypted byte.
    unsigned __int8                 readUnencrypted();

    //reads in an unencrypted byte.
    unsigned __int8                 getUnencrypted();

    //reads in an unencrypted byte array to the buffer.
    void                            readUnencrypted(char buffer[], int);
};
