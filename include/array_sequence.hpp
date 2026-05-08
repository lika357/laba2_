#pragma once
#include "dynamic_array.hpp"
#include "sequence.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
   private:
    DynamicArray<T>* items;

   public:
    ArraySequence()
    {
        items = new DynamicArray<T>();
    }
    template <size_t N>
    ArraySequence(T (&arr)[N])
    {
        items = new DynamicArray<T>(arr);
    }
};
