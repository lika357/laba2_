#pragma once
#include <cstddef>

#include "exceptions.hpp"

template <typename T>
class DynamicArray
{
   private:
    T* data;
    size_t size;

   public:
    DynamicArray() : data{nullptr}, size{0}
    {
    }

    DynamicArray(size_t count) : data{nullptr}, size{0}
    {
        size = count;
        data = new T[size];
    }

    template <size_t N>
    DynamicArray(T (&items)[N]) : DynamicArray{N}
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = items[i];
        }
    }
};