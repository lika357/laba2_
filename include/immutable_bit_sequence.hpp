#pragma once
#include "sequence.hpp"
#include "dynamic_array.hpp"
#include "bit.hpp"
#include "exceptions.hpp"

template <typename T = unsigned char>
class ImmutableBitSequence : public Sequence<Bit<T>>
{
   private:
    DynamicArray<Bit<T>>* bits;

   public:
    ImmutableBitSequence()
    {
        bits = new DynamicArray<Bit<T>>();
    }

    template <size_t N>
    ImmutableBitSequence(Bit<T> (&arr)[N])
    {
        bits = new DynamicArray<Bit<T>>(arr);
    }

    ImmutableBitSequence(const ImmutableBitSequence<T>& other)
    {
        bits = new DynamicArray<Bit<T>>(*other.bits);
    }

    ~ImmutableBitSequence()
    {
        delete bits;
    }

    const Bit<T>& operator[](size_t index) const
    {
        return (*bits)[index];
    }

    Bit<T> GetFirst() const override
    {
        if (bits->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return bits->Get(0);
    }

    Bit<T> GetLast() const override
    {
        if (bits->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return bits->Get(bits->GetSize() - 1);
    }

    Bit<T> Get(size_t index) const override
    {
        return bits->Get(index);
    }

    size_t GetLength() const override
    {
        return bits->GetSize();
    }

    Sequence<Bit<T>>* GetSubsequence(size_t start, size_t end) const override
    {
        ImmutableBitSequence<T>* result = new ImmutableBitSequence<T>();
        for (size_t i = start; i <= end; i++)
        {
            result->bits->Resize(result->bits->GetSize() + 1);
            result->bits->Set(result->bits->GetSize() - 1, bits->Get(i));
        }
        return result;
    }

    ImmutableBitSequence<T> operator&(const ImmutableBitSequence<T>& other) const
    {
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> andResult = bits->Get(i) & other.bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, andResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator|(const ImmutableBitSequence<T>& other) const
    {
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> orResult = bits->Get(i) | other.bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, orResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator^(const ImmutableBitSequence<T>& other) const
    {
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> xorResult = bits->Get(i) ^ other.bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, xorResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator~() const
    {
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits->GetSize(); i++)
        {
            Bit<T> notResult = ~bits->Get(i);
            result.bits->Resize(i + 1);
            result.bits->Set(i, notResult);
        }
        return result;
    }
};