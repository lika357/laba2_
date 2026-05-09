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
    BitProxy& operator=(bool val)
    {
        if (val)
        {
            ref = ref | (static_cast<T>(1) << idx);
        }
        else
        {
            ref = ref & ~(static_cast<T>(1) << idx);
        }
        return *this;
    }
    operator bool() const
    {
        return (ref >> idx) & 1;
    }
};

template <typename T = unsigned char>
class Bit
{
   private:
    T value;

   public:
    Bit() : value{0}
    {
    }
    Bit(T val) : value{val}
    {
    }
    Bit(const Bit& other) : value{other.value}
    {
    }
    T GetValue() const
    {
        return value;
    }
    operator bool() const
    {
        return value != 0;
    }
    Bit operator&(const Bit& other) const
    {
        T result = value & other.value;
        Bit b(result);
        return b;
    }
    Bit operator|(const Bit& other) const
    {
        T result = value | other.value;
        Bit b(result);
        return b;
    }
    Bit operator^(const Bit& other) const
    {
        T result = value ^ other.value;
        Bit b(result);
        return b;
    }
    Bit operator~() const
    {
        T result = ~value;
        Bit b(result);
        return b;
    }
};