#pragma once
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include "sequence.hpp"

template <typename T>
class ImmutableArraySequence : public Sequence<T>
{
   private:
    DynamicArray<T>* items;

   public:
    ImmutableArraySequence()
    {
        items = new DynamicArray<T>();
    }

    template <size_t N>
    ImmutableArraySequence(T (&arr)[N])
    {
        items = new DynamicArray<T>(arr);
    }

    ImmutableArraySequence(const ImmutableArraySequence<T>& other)
    {
        items = new DynamicArray<T>(*other.items);
    }

    ~ImmutableArraySequence()
    {
        delete items;
    }

    T GetFirst() const override
    {
        if (items->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return items->Get(0);
    }

    T GetLast() const override
    {
        if (items->GetSize() == 0)
        {
            throw IndexOutOfRange{};
        }
        return items->Get(items->GetSize() - 1);
    }

    T Get(size_t index) const override
    {
        return items->Get(index);
    }

    size_t GetLength() const override
    {
        return items->GetSize();
    }

    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->Append(items->Get(i));
        }
        return result;
    }

    T& operator[](size_t index)
    {
        return (*items)[index];
    }

    const T& operator[](size_t index) const
    {
        return (*items)[index];
    }
};