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