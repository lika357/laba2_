#pragma once
#include <exception>
#include <string>

class Exceptions : public std::exception
{
   protected:
    std::string message;

   public:
    Exceptions(const std::string& msg) : message{msg} {}
    const char* what() const noexcept override { return message.c_str(); }
};

class IndexOutOfRange : public Exceptions
{
   public:
    IndexOutOfRange() : Exceptions{"Ошибка : индекс вышел за границы массива"}
    {
    }
};