/*$6*/


#pragma once
template<class T>
class BasylArray
{
private:
    T   *data;
    int len;
public:
    BasylArray();
    BasylArray(const BasylArray<T> &c);
    BasylArray(int size);
    BasylArray(T *arr, int s);
    ~                       BasylArray();

    T &operator             [](size_t idx);
    const T &operator       [](size_t idx) const;

    int                     size() const;
    BasylArray<T> &operator =(const BasylArray<T> &z);
};
