/*$6*/


#pragma once
typedef unsigned __int8 byte;
#include <string>

//Written as an addition later on. I'm still a bit new to abstract classes in C++.
class   IBasylKeyGenerator
{
public:
    virtual byte    GetRandomByte() = 0;

    virtual void    Encrypt(__int8 &) = 0;
    virtual void    Encrypt(byte &) = 0;

    virtual void    Encrypt(__int8[], int size) = 0;
    virtual void    Encrypt(byte[], int size) = 0;
    virtual void    Encrypt(std::string) = 0;
};
