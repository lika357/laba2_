#pragma once
#include "bit.hpp"
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include "sequence.hpp"

template <typename T = unsigned char>
class ImmutableBitSequence : public Sequence<Bit<T>>
{
   private:
    DynamicArray<Bit<T>> bits;

   public:
    ImmutableBitSequence() : bits{}
    {
    }

    template <size_t N>
    ImmutableBitSequence(Bit<T> (&arr)[N]) : bits{arr}
    {
    }

    ImmutableBitSequence(const ImmutableBitSequence<T>& other) : bits{other.bits}
    {
    }

    const Bit<T>& operator[](size_t index) const
    {
        if (index >= bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        return bits[index];
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

    Sequence<Bit<T>>* GetSubsequence(size_t start, size_t end) const override
    {
        if (start > end || end >= bits.GetSize())
        {
            throw InvalidArgument{};
        }
        ImmutableBitSequence<T>* result = new ImmutableBitSequence<T>();
        for (size_t i = start; i <= end; i++)
        {
            result->bits.Resize(result->bits.GetSize() + 1);
            result->bits.Set(result->bits.GetSize() - 1, bits.Get(i));
        }
        return result;
    }

    ImmutableBitSequence<T> operator&(const ImmutableBitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> andResult = bits.Get(i) & other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, andResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator|(const ImmutableBitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> orResult = bits.Get(i) | other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, orResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator^(const ImmutableBitSequence<T>& other) const
    {
        if (bits.GetSize() != other.bits.GetSize())
        {
            throw InvalidArgument{};
        }
        ImmutableBitSequence<T> result;
        for (size_t i = 0; i < bits.GetSize(); i++)
        {
            Bit<T> xorResult = bits.Get(i) ^ other.bits.Get(i);
            result.bits.Resize(i + 1);
            result.bits.Set(i, xorResult);
        }
        return result;
    }

    ImmutableBitSequence<T> operator~() const
    {
        ImmutableBitSequence<T> result;
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
        ImmutableBitSequence<T>* copy = new ImmutableBitSequence<T>(*this);
        copy->bits.Resize(copy->bits.GetSize() + 1);
        copy->bits.Set(copy->bits.GetSize() - 1, item);
        return copy;
    }

    Sequence<Bit<T>>* Prepend(Bit<T> item) override
    {
        ImmutableBitSequence<T>* copy = new ImmutableBitSequence<T>(*this);
        size_t oldSize = copy->bits.GetSize();
        copy->bits.Resize(oldSize + 1);
        for (size_t i = oldSize; i > 0; i--)
        {
            copy->bits.Set(i, copy->bits.Get(i - 1));
        }
        copy->bits.Set(0, item);
        return copy;
    }

    Sequence<Bit<T>>* InsertAt(Bit<T> item, size_t index) override
    {
        if (index > bits.GetSize())
        {
            throw IndexOutOfRange{index, bits.GetSize()};
        }
        ImmutableBitSequence<T>* copy = new ImmutableBitSequence<T>(*this);
        size_t oldSize = copy->bits.GetSize();
        copy->bits.Resize(oldSize + 1);
        for (size_t i = oldSize; i > index; i--)
        {
            copy->bits.Set(i, copy->bits.Get(i - 1));
        }
        copy->bits.Set(index, item);
        return copy;
    }

    Sequence<Bit<T>>* Concat(Sequence<Bit<T>>* other) override
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }
        ImmutableBitSequence<T>* copy = new ImmutableBitSequence<T>(*this);
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            copy->bits.Resize(copy->bits.GetSize() + 1);
            copy->bits.Set(copy->bits.GetSize() - 1, other->Get(i));
        }
        return copy;
    }
};