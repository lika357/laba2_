#pragma once
#include <cstddef>

#include "exceptions.hpp"

template <typename T>
class LinkedList
{
   private:
    struct Node
    {
        T value;
        Node* next;
        Node(const T& val) : value{val}, next{nullptr}
        {
        }
    };

    Node* head;
    size_t length;

   public:
    LinkedList() : head{nullptr}, length{0}
    {
    }
};