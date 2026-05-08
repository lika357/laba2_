#pragma once
#include "dynamic_array.hpp"
#include "sequence.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
   private:
    DynamicArray<T>* items;

   public:
    ArraySequence()
    {
        items = new DynamicArray<T>();
    }
    template <size_t N>
    ArraySequence(T (&arr)[N])
    {
        items = new DynamicArray<T>(arr);
    }
    ArraySequence(const ArraySequence<T>& other)
    {
        items = new DynamicArray<T>(*other.items);
    }
    ~ArraySequence()
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
    Sequence<T>* Append(T item) override
    {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, item);
        return this;
    }
    Sequence<T>* Prepend(T item) override
    {
        size_t oldSize = items->GetSize();
        items->Resize(oldSize + 1);
        for (size_t i = oldSize; i > 0; i--)
        {
            items->Set(i, items->Get(i - 1));
        }
        items->Set(0, item);
        return this;
    }
};
