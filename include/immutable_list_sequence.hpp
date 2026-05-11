#pragma once
#include "exceptions.hpp"
#include "linked_list.hpp"
#include "sequence.hpp"

template <typename T>
class ImmutableListSequence : public Sequence<T>
{
   private:
    LinkedList<T> items;

   public:
    ImmutableListSequence() : items{}
    {
    }

    template <size_t N>
    ImmutableListSequence(T (&arr)[N]) : items{arr}
    {
    }

    ImmutableListSequence(const ImmutableListSequence<T>& other) : items{other.items}
    {
    }

    T GetFirst() const override
    {
        if (items.GetLength() == 0)
        {
            throw IndexOutOfRange{0, items.GetLength()};
        }
        return items.GetFirst();
    }

    T GetLast() const override
    {
        if (items.GetLength() == 0)
        {
            throw IndexOutOfRange{0, items.GetLength()};
        }
        return items.GetLast();
    }

    T Get(size_t index) const override
    {
        if (index >= items.GetLength())
        {
            throw IndexOutOfRange{index, items.GetLength()};
        }
        return items.Get(index);
    }

    size_t GetLength() const override
    {
        return items.GetLength();
    }

    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        if (startIndex > endIndex || endIndex >= items.GetLength())
        {
            throw InvalidArgument{};
        }
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->items.Append(items.Get(i));
        }
        return result;
    }

    const T& operator[](size_t index) const
    {
        if (index >= items.GetLength())
        {
            throw IndexOutOfRange{index, items.GetLength()};
        }
        return items[index];
    }

    Sequence<T>* Append(T item) override
    {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items.Append(item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override
    {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items.Prepend(item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, size_t index) override
    {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items.InsertAt(item, index);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* other) override
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            copy->items.Append(other->Get(i));
        }
        return copy;
    }
};