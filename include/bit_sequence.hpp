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
    Bit<T> GetLast() const
    {
        if (bits->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return bits->Get(bits->GetSize() - 1);
    }
    Bit<T> Get(size_t index) const
    {
        return bits->Get(index);
    }
    size_t GetLength() const
    {
        return bits->GetSize();
    }
    BitSequence<T> operator&(const BitSequence<T>& other) const
    {
        BitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> andResult = bits->Get(i) & other.bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, andResult);
        }
        return result;
    }
    Bit<T>& operator[](size_t index)
    {
        return (*bits)[index];
    }

    const Bit<T>& operator[](size_t index) const
    {
        return (*bits)[index];
    }
    BitSequence<T> operator|(const BitSequence<T>& other) const
    {
        BitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> orResult = bits->Get(i) | other.bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, orResult);
        }
        return result;
    }
};