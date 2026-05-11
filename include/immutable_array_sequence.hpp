#pragma once
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include "sequence.hpp"

template <typename T>
class ImmutableArraySequence : public Sequence<T>
{
   private:
    DynamicArray<T> items;

   public:
    ImmutableArraySequence() : items{}
    {
    }

    template <size_t N>
    ImmutableArraySequence(T (&arr)[N]) : items{arr}
    {
    }

    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : items{other.items}
    {
    }

    T GetFirst() const override
    {
        if (items.GetSize() == 0)
        {
            throw IndexOutOfRange{0, items.GetSize()};
        }
        return items.Get(0);
    }

    T GetLast() const override
    {
        if (items.GetSize() == 0)
        {
            throw IndexOutOfRange{0, items.GetSize()};
        }
        return items.Get(items.GetSize() - 1);
    }

    T Get(size_t index) const override
    {
        if (index >= items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        return items.Get(index);
    }

    size_t GetLength() const override
    {
        return items.GetSize();
    }

    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        if (startIndex > endIndex || endIndex >= items.GetSize())
        {
            throw InvalidArgument{};
        }
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->Append(items.Get(i));
        }
        return result;
    }

    const T& operator[](size_t index) const
    {
        if (index >= items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        return items[index];
    }

    Sequence<T>* Append(T item) override
    {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        copy->items.Resize(copy->items.GetSize() + 1);
        copy->items.Set(copy->items.GetSize() - 1, item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override
    {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        size_t oldSize = copy->items.GetSize();
        copy->items.Resize(oldSize + 1);
        for (size_t i = oldSize; i > 0; i--)
        {
            copy->items.Set(i, copy->items.Get(i - 1));
        }
        copy->items.Set(0, item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, size_t index) override
    {
        if (index > items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        size_t oldSize = copy->items.GetSize();
        copy->items.Resize(oldSize + 1);
        for (size_t i = oldSize; i > index; i--)
        {
            copy->items.Set(i, copy->items.Get(i - 1));
        }
        copy->items.Set(index, item);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* other) override
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            copy->items.Resize(copy->items.GetSize() + 1);
            copy->items.Set(copy->items.GetSize() - 1, other->Get(i));
        }
        return copy;
    }
};