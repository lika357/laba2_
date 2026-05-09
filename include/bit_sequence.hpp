#pragma once
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "sequence.hpp"

template <typename T = unsigned char>
class BitSequence
{
   private:
    DynamicArray<Bit<T>>* bits;

   public:
    BitSequence()
    {
        bits = new DynamicArray<Bit<T>>();
    }
    template <size_t N>
    BitSequence(Bit<T> (&arr)[N])
    {
        bits = new DynamicArray<Bit<T>>(arr);
    }
    BitSequence(const BitSequence<T>& other)
    {
        bits = new DynamicArray<Bit<T>>(*other.bits);
    }
    ~BitSequence()
    {
        delete bits;
    }
    Bit<T> GetFirst() const
    {
        if (bits->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return bits->Get(0);
    }
};