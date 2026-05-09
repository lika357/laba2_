#pragma once
#include <cstddef>

template <typename T = unsigned char>
class BitProxy
{
   private:
    T& ref;
    size_t idx;

   public:
    BitProxy(T& value, size_t index) : ref{value}, idx{index}
    {
    }
};