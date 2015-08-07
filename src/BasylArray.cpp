/*$6*/


#include "BasylArray.h"

template class BasylArray<int>;
template class BasylArray < unsigned int >;
template class BasylArray < unsigned __int8 >;

template<class T>
BasylArray<T>::BasylArray (int size) :
    data(new T[size]()),
    len(size)
{
}
template<class T>
BasylArray<T>::BasylArray() :
    data(nullptr),
    len(0)
{
}
template<class T>
BasylArray<T>::BasylArray(T * arr, int size) :
    data(new T[size]()),
    len(size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = arr[i];
    }
}
template<class T>
BasylArray<T>::BasylArray (const BasylArray<T> &c) :
    data(new T[c.size()]()),
    len(c.size())
{
    for (int i = 0; i < c.size(); i++)
    {
        data[i] = c[i];
    }
}
template<class T>
BasylArray<T>::~BasylArray()
{
    delete[] data;
}

template<class T>
BasylArray<T> &BasylArray<T>::operator=(const BasylArray<T> &z)
{
    this->data = new T[z.size()]();
    for (int i = 0; i < z.size(); i++)
    {
        this->data[i] = z[i];
    }

    this->len = z.size();
    return *this;
}

template<class T>
int BasylArray<T>::size() const
{
    return this->len;
}
template<class T>
T &BasylArray<T>::operator[](size_t idx)
{
    return data[idx];
}

template<class T>
const T &BasylArray<T>::operator[](size_t idx) const
{
    return data[idx];
}
