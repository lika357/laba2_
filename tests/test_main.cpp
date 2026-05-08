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
    test_linked_list_copy();
    test_linked_list_destructor();
    test_linked_list_assignment();
    test_linked_list_index();
    test_linked_list_const_index();
    test_linked_list_first();
    test_linked_list_last();
    test_linked_list_get();
    test_linked_list_length();
    test_linked_list_prepend();
    test_linked_list_insert();
    test_linked_list_sublist();
    test_linked_list_concat();
    test_linked_list_exceptions();
    test_sequence_exists();
    test_array_sequence_empty();
    test_list_sequence_empty();
    test_array_sequence_from_array();
    test_list_sequence_from_array();
    test_array_sequence_copy();
    test_list_sequence_copy();
    test_array_sequence_destructor();
    test_list_sequence_destructor();
    test_array_sequence_get_first();
    test_list_sequence_get_first();
    test_array_sequence_get_last();
    test_list_sequence_get_last();
    test_array_sequence_get();
    test_list_sequence_get();
    test_array_sequence_length();
    test_list_sequence_length();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}