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
};