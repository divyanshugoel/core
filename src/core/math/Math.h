// Copyright 2022 Divyanshu Goel.
#pragma once

#include <cmath>

#include <limits>
#include <type_traits>

#include "core/math/Constants.h"

////////////////////////////////////////////////////////////////////////////////
// Defines the basic mathematical functions for the core
namespace fms
{

////////////////////////////////////////////////////////////////////////////////
// sigNum function returns -1, 1, 0.
inline int sign(double value)
{
    if (fabs(value) <= largeEpsilon)
        return 0;
    else if (value < 0)
        return -1;
    else
        return 1;
}

////////////////////////////////////////////////////////////////////////////////

inline double safeDivide(double A, double B)
{
    if (B == 0)
    {
        if (fms::sign(A) == -1)
            return -std::numeric_limits<double>::infinity();
        if (fms::sign(A) == 1)
            return std::numeric_limits<double>::infinity();
        if (fms::sign(A) == 0)
            return 0;
    }
    return A / B;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace fms
