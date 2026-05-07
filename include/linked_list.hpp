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
    template <size_t N>
    LinkedList(T (&items)[N]) : head{nullptr}, length{0}
    {
        for (size_t i = 0; i < N; i++)
        {
            Append(items[i]);
        }
    }
    LinkedList(const LinkedList<T>& other) : head{nullptr}, length{0}
    {
        Node* current = other.head;
        while (current != nullptr)
        {
            Append(current->value);
            current = current->next;
        }
    }
    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    LinkedList<T>& operator=(const LinkedList<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;

        Node* current = other.head;
        while (current != nullptr)
        {
            Append(current->value);
            current = current->next;
        }

        return *this;
    }
    T& operator[](size_t index)
    {
        if (index >= length)
        {
            throw IndexOutOfRange{};
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }

    const T& operator[](size_t index) const
    {
        if (index >= length)
        {
            throw IndexOutOfRange{};
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }
    T GetFirst() const
    {
        if (head == nullptr)
        {
            throw IndexOutOfRange{};
        }
        return head->value;
    }
    T GetLast() const
    {
        if (head == nullptr)
        {
            throw IndexOutOfRange{};
        }
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->value;
    }
    T Get(size_t index) const
    {
        if (index >= length)
        {
            throw IndexOutOfRange{};
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }
    size_t GetLength() const
    {
        return length;
    }
    void Prepend(T item)
    {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        length++;
    }
    void InsertAt(T item, size_t index)
    {
        if (index > length)
        {
            throw IndexOutOfRange{};
        }

        if (index == 0)
        {
            Prepend(item);
            return;
        }

        if (index == length)
        {
            Append(item);
            return;
        }

        Node* newNode = new Node(item);
        Node* current = head;
        for (size_t i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        length++;
    }
    LinkedList<T>* GetSubList(size_t from, size_t to) const
    {
        if (from > to || to >= length)
        {
            throw InvalidArgument{};
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        for (size_t i = 0; i < from; i++)
        {
            current = current->next;
        }
        for (size_t i = from; i <= to; i++)
        {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }
    LinkedList<T>* Concat(LinkedList<T>* other) const
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        while (current != nullptr)
        {
            result->Append(current->value);
            current = current->next;
        }
        current = other->head;
        while (current != nullptr)
        {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }
};