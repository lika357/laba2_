#include <iostream>

#include "assert.hpp"
#include "test.hpp"

int main()
{
    test_exception_what();
    test_exception_catch_1();
    test_exception_catch_2();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}