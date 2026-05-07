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
    DynamicArray(const DynamicArray<T>& other) : DynamicArray{other.size}
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    ~DynamicArray()
    {
        delete[] data;
    }
    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] data;
        size = other.size;
        data = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }
    T& operator[](size_t index)
    {
        if (index >= size)
        {
            throw IndexOutOfRange{};
        }
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size)
        {
            throw IndexOutOfRange{};
        }
        return data[index];
    }
    T Get(size_t index) const
    {
        if (index >= size)
        {
            throw IndexOutOfRange{};
        }
        return data[index];
    }
};