#pragma once

template <class T>
class Sequence
{
   public:
    virtual ~Sequence() = default;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
};