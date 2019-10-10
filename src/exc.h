#pragma once
#include <exception>

class exc_notsolvable : std::exception
{
public:
    using std::exception::exception;
};