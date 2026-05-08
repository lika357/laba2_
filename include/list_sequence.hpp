#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"

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