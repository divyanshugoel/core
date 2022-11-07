// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>

#include "core/core/MacroExpansions.h"
#include "core/math/Constants.h"

////////////////////////////////////////////////////////////////////////////////
// Implementations for Core.h macros and functions
////////////////////////////////////////////////////////////////////////////////
#define BIT(x) (1 << (x))

#define GET_MACRO(value, NAME, ...) NAME_()

#define FMS_CHECK_AND_RETURN_VAL(condition, value) \
    if (condition)                                 \
        return value;

////////////////////////////////////////////////////////////////////////////////

#define FMS_CHECK_AND_RETURN(condition) \
    if (condition)                      \
        return;

////////////////////////////////////////////////////////////////////////////////

#define FMS_CHECK_AND_RETURN_IMPL(...)                                     \
    GET_MACRO(__VA_ARGS__, FMS_CHECK_AND_RETURN_VAL, FMS_CHECK_AND_RETURN) \
    (__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
// Deletes the copy constructor and assignment operator

#define FMS_DECLARE_NON_COPYABLE(ClassName) \
    ClassName(const ClassName&) = delete;   \
    ClassName& operator=(const ClassName&) = delete

////////////////////////////////////////////////////////////////////////////////
