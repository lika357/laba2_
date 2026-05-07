#include "../include/dynamic_array.hpp"
#include "../include/exceptions.hpp"
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