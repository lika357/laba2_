#pragma once
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include "sequence.hpp"

template <typename T = unsigned char>
class BitSequence : public Sequence<Bit<T>>
{
   private:
    DynamicArray<Bit<T>> bits;

   public:
    BitSequence() : bits{}
    {
    }
    template <size_t N>
    BitSequence(Bit<T> (&arr)[N]) : bits{arr}
    {
    }
    BitSequence(const BitSequence<T>& other) : bits{other.bits}
    {
    }
    Bit<T> GetFirst() const override
    {
        if (bits.GetSize() == 0)
        {
            throw IndexOutOfRange{0, bits.GetSize()};
        }
        return bits.Get(0);
    }
    Bit<T> GetLast() const override
    {
        if (bits.GetSize() == 0)
        {
            throw IndexOutOfRange{0, bits.GetSize()};
        }
        return bits.Get(bits.GetSize() - 1);
    }
    Bit<T> Get(size_t index) const override
    {
        if (index >= bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        return bits.Get(index);
    }
    size_t GetLength() const override
    {
        return bits.GetSize();
    }
    BitSequence<T> operator&(const BitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        BitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> andResult = bits.Get(i) & other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, andResult);
        }
        return result;
    }
    Bit<T>& operator[](size_t index)
    {
        if (index >= bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        return bits[index];
    }

    const Bit<T>& operator[](size_t index) const
    {
        if (index >= bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        return bits[index];
    }
    BitSequence<T> operator|(const BitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        BitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> orResult = bits.Get(i) | other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, orResult);
        }
        return result;
    }
    BitSequence<T> operator^(const BitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        BitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> xorResult = bits.Get(i) ^ other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, xorResult);
        }
        return result;
    }
    BitSequence<T> operator~() const
    {
        BitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> notResult = ~bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, notResult);
        }
        return result;
    }
    Sequence<Bit<T>>* Append(Bit<T> item) override
    {
        bits.Resize(bits.GetSize() + 1);
        bits.Set(bits.GetSize() - 1, item);
        return this;
    }
    Sequence<Bit<T>>* Prepend(Bit<T> item) override
    {
        size_t oldSize = bits.GetSize();
        bits.Resize(oldSize + 1);
        for (size_t i = oldSize; i > 0; i--)
        {
            bits.Set(i, bits.Get(i - 1));
        }
        bits.Set(0, item);
        return this;
    }
    Sequence<Bit<T>>* InsertAt(Bit<T> item, size_t index) override
    {
        if (index > bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        size_t oldSize = bits.GetSize();
        bits.Resize(oldSize + 1);
        for (size_t i = oldSize; i > index; i--)
        {
            bits.Set(i, bits.Get(i - 1));
        }
        bits.Set(index, item);
        return this;
    }
    Sequence<Bit<T>>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        if (startIndex > endIndex || endIndex >= bits.GetSize())
        {
            throw InvalidArgument{};
        }
        BitSequence<T>* result = new BitSequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->Append(bits.Get(i));
        }
        return result;
    }
    Sequence<Bit<T>>* Concat(Sequence<Bit<T>>* other) override
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            Append(other->Get(i));
        }
        return this;
    }
};