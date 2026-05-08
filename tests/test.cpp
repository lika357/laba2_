#include "../include/dynamic_array.hpp"
#include "../include/exceptions.hpp"
#include "../include/linked_list.hpp"
#include "assert.hpp"

void test_exception_what()
{
    IndexOutOfRange e;
    assert_func(e.what() != nullptr);
}

void test_exception_catch_1()
{
    bool caught = false;
    try
    {
        throw IndexOutOfRange{};
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);
}

void test_exception_catch_2()
{
    bool caught = false;
    try
    {
        throw IndexOutOfRange{};
    }
    catch (const IndexOutOfRange&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_invalid_argument()
{
    bool caught = false;
    try
    {
        throw InvalidArgument{};
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_null_pointer()
{
    bool caught = false;
    try
    {
        throw NullPointer{};
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_dynamic_array_constructors()
{
    DynamicArray<int> a(0);
    assert_func(true);

    DynamicArray<int> b(5);
    assert_func(true);

    int items[] = {1, 2, 3};
    DynamicArray<int> c(items);
    assert_func(true);
}
void test_dynamic_array_copy()
{
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items);
    DynamicArray<int> b(a);
    assert_func(true);
}
void test_dynamic_array_assign()
{
    int items[] = {10, 20, 30};
    DynamicArray<int> a(items);
    DynamicArray<int> b(0);
    b = a;
    assert_func(true);
}
void test_dynamic_array_index()
{
    int items[] = {10, 20, 30};
    DynamicArray<int> a(items);
    assert_func(a[0] == 10);
    assert_func(a[1] == 20);
    assert_func(a[2] == 30);
}
void test_dynamic_array_const_index()
{
    int items[] = {10, 20, 30};
    const DynamicArray<int> a(items);

    assert_func(a[0] == 10);
    assert_func(a[1] == 20);
    assert_func(a[2] == 30);
}
void test_dynamic_array_get()
{
    int items[] = {10, 20, 30};
    DynamicArray<int> a(items);
    assert_func(a.Get(0) == 10);
    assert_func(a.Get(1) == 20);
    assert_func(a.Get(2) == 30);
}
void test_dynamic_array_size()
{
    DynamicArray<int> a(5);
    assert_func(a.GetSize() == 5);

    int items[] = {1, 2, 3};
    DynamicArray<int> b(items);
    assert_func(b.GetSize() == 3);
}
void test_dynamic_array_set()
{
    DynamicArray<int> a(3);
    a.Set(0, 10);
    a.Set(1, 20);
    a.Set(2, 30);
    assert_func(a.Get(0) == 10);
    assert_func(a.Get(1) == 20);
    assert_func(a.Get(2) == 30);
}
void test_dynamic_array_resize()
{
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items);

    a.Resize(5);
    assert_func(a.GetSize() == 5);
    assert_func(a.Get(0) == 1);
    assert_func(a.Get(2) == 3);

    a.Resize(2);
    assert_func(a.GetSize() == 2);
    assert_func(a.Get(0) == 1);
    assert_func(a.Get(1) == 2);
}
void test_dynamic_array_exceptions()
{
    DynamicArray<int> a(3);
    bool caught = false;

    try
    {
        a.Get(5);
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        a.Set(5, 0);
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        a[5] = 10;
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    const DynamicArray<int> b(3);
    caught = false;
    try
    {
        b[5];
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_linked_list()
{
    LinkedList<int> list;
    assert_func(true);
}
void test_linked_list_append()
{
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    assert_func(true);
}
void test_linked_list_from_array()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(true);
}
void test_linked_list_copy()
{
    int items[] = {1, 2, 3};
    LinkedList<int> a(items);
    LinkedList<int> b(a);
    assert_func(true);
}
void test_linked_list_destructor()
{
    int items[] = {1, 2, 3};
    {
        LinkedList<int> list(items);
    }
    assert_func(true);
}
void test_linked_list_assignment()
{
    int items[] = {10, 20, 30};
    LinkedList<int> a(items);
    LinkedList<int> b;
    b = a;
    assert_func(true);
}
void test_linked_list_index()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(list[0] == 10);
    assert_func(list[1] == 20);
    assert_func(list[2] == 30);
}
void test_linked_list_const_index()
{
    int items[] = {10, 20, 30};
    const LinkedList<int> list(items);
    assert_func(list[0] == 10);
    assert_func(list[1] == 20);
    assert_func(list[2] == 30);
}
void test_linked_list_first()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(list.GetFirst() == 10);
}
void test_linked_list_last()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(list.GetLast() == 30);
}
void test_linked_list_get()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(list.Get(0) == 10);
    assert_func(list.Get(1) == 20);
    assert_func(list.Get(2) == 30);
}
void test_linked_list_length()
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items);
    assert_func(list.GetLength() == 3);
}
void test_linked_list_prepend()
{
    LinkedList<int> list;
    list.Prepend(30);
    list.Prepend(20);
    list.Prepend(10);
    assert_func(true);
}
void test_linked_list_insert()
{
    int items[] = {10, 30};
    LinkedList<int> list(items);
    list.InsertAt(20, 1);
    assert_func(true);
}
void test_linked_list_sublist()
{
    int items[] = {10, 20, 30, 40, 50};
    LinkedList<int> list(items);
    LinkedList<int>* sub = list.GetSubList(1, 3);
    assert_func(sub->GetLength() == 3);
    assert_func(sub->Get(0) == 20);
    assert_func(sub->Get(2) == 40);
    delete sub;
}
void test_linked_list_concat()
{
    int a[] = {1, 2};
    int b[] = {3, 4};
    LinkedList<int> listA(a);
    LinkedList<int> listB(b);
    LinkedList<int>* merged = listA.Concat(&listB);
    assert_func(merged->GetLength() == 4);
    assert_func(merged->Get(0) == 1);
    assert_func(merged->Get(3) == 4);
    delete merged;
}
void test_linked_list_exceptions()
{
    LinkedList<int> empty;
    bool caught = false;

    try
    {
        empty.GetFirst();
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        empty.GetLast();
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    int items[] = {1, 2};
    LinkedList<int> list(items);
    caught = false;
    try
    {
        list.Get(5);
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        list.InsertAt(0, 5);
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        list.Concat(nullptr);
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);

    caught = false;
    try
    {
        list[5];
    }
    catch (const Exceptions&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_sequence_exists()
{
    assert_func(true);
}