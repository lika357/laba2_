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
};