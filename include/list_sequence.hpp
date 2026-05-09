#pragma once
#include "linked_list.hpp"
#include "sequence.hpp"

template <class T>
class ListSequence : public Sequence<T>
{
   private:
    LinkedList<T>* items;

   public:
    ListSequence()
    {
        items = new LinkedList<T>();
    }
    template <size_t N>
    ListSequence(T (&arr)[N])
    {
        items = new LinkedList<T>(arr);
    }
    ListSequence(const ListSequence<T>& other)
    {
        items = new LinkedList<T>(*other.items);
    }
    ~ListSequence()
    {
        delete items;
    }
    T GetFirst() const override
    {
        if (items->GetLength() == 0)
        {
            throw IndexOutOfRange{};
        }
        return items->GetFirst();
    }
    T GetLast() const override
    {
        if (items->GetLength() == 0)
        {
            throw IndexOutOfRange{};
        }
        return items->GetLast();
    }
    T Get(size_t index) const override
    {
        return items->Get(index);
    }
    size_t GetLength() const override
    {
        return items->GetLength();
    }
    Sequence<T>* Append(T item) override
    {
        items->Append(item);
        return this;
    }
    Sequence<T>* Prepend(T item) override
    {
        items->Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(T item, size_t index) override
    {
        items->InsertAt(item, index);
        return this;
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        ListSequence<T>* result = new ListSequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->Append(items->Get(i));
        }
        return result;
    }
    Sequence<T>* Concat(Sequence<T>* other) override
    {
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            Append(other->Get(i));
        }
        return this;
    }
};