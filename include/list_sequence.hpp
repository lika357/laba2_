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
};