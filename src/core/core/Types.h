// Copyright 2022 Divyanshu Goel.
#pragma once

#include <functional>
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Define the param type.
enum class crDataType
{
    DOUBLE = 0,
    FLOAT = 1,
    INT = 2,
    UINT = 3,
    STRING = 4,
    BOOL = 5,
    CHAR = 6,
    NONE = 7
};

////////////////////////////////////////////////////////////////////////////////
// Define a way to handle the name only basic names

template <typename T>
struct TypeInfo;

#define REGISTER_TYPE(X, Y)             \
    template <>                         \
    struct TypeInfo<X>                  \
    {                                   \
        static const char* name;        \
        static const X defaultValue;    \
    };                                  \
    const char* TypeInfo<X>::name = #X; \
    const X TypeInfo<X>::defaultValue = Y

template <typename T>
using ParamValidatorFunctor = std::function<bool(const T&)>;
