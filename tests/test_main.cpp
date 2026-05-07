#include <iostream>

#include "assert.hpp"
#include "test.hpp"

int main()
{
    test_exception_what();
    test_exception_catch_1();
    test_exception_catch_2();
    test_invalid_argument();
    test_null_pointer();
    test_dynamic_array_constructors();
    test_dynamic_array_copy();
    test_dynamic_array_assign();
    test_dynamic_array_index();
    test_dynamic_array_const_index();
    test_dynamic_array_get();
    test_dynamic_array_size();
    test_dynamic_array_set();
    test_dynamic_array_resize();
    test_dynamic_array_exceptions();
    test_linked_list();
    test_linked_list_append();
    test_linked_list_from_array();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}