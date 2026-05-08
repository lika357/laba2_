#pragma once
#include "sequence.hpp"
#include "dynamic_array.hpp"

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
};
