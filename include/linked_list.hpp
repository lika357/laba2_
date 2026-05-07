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
    void Append(T item)
    {
        Node* newNode = new Node(item);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }
};