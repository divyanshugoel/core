// Copyright 2022 Divyanshu Goel.
#pragma once

#include <stdarg.h>
#include <stdio.h>

#include <cmath>

#include <string>

#include "core/math/Constants.h"

////////////////////////////////////////////////////////////////////////////////

inline bool FMS_APPROX(double valueA, double valueB)
{
    return fabs(valueA - valueB) <= largeEpsilon;
}

////////////////////////////////////////////////////////////////////////////////

inline bool FMS_APPROX(double value)
{
    return fabs(value) <= largeEpsilon;
}

////////////////////////////////////////////////////////////////////////////////

inline void fmsPrintInternal(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf(".\n");
}

////////////////////////////////////////////////////////////////////////////////

inline void fmsPrintInternalNoEnd(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////

inline void fmsPrintRepeated(const std::string& fmt, int value)
{
    std::string out = "";
    for (int i = 0; i < value; i++)
    {
        out.append(fmt);
    }
    fmsPrintInternalNoEnd("%s", out.c_str());
}

////////////////////////////////////////////////////////////////////////////////

inline void fmsPrintColor(const char* color, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("%s", color);
    vprintf(fmt, args);
    va_end(args);
    printf(".\n");
    printf("\033[0m");
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool checkNumber(const T& value)
{
    if (std::is_arithmetic<T>::value)
    {
        if (std::isnan(value) || std::isinf(value))
        {
            fmsPrintInternal("Invalid Input");
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        fmsPrintInternal("Invalid Type");
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool checkNumberPositive(const T& value)
{
    if (!checkNumber<T>(value))
        return false;
    else
    {
        if (value > 0)
            return true;
        else
            return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool checkNumberNonPositive(const T& value)
{
    return !checkNumberPositive(value);
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool checkNumberNegative(const T& value)
{
    if (!checkNumber<T>(value))
        return false;
    else
    {
        if (value < 0)
            return true;
        else
            return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool checkNumberNonNegative(const T& value)
{
    return !checkNumberNegative(value);
}

////////////////////////////////////////////////////////////////////////////////

// inline void checkAndReturn(bool condition, const std::string& message)
// {
//     if (!condition)
//     {
//         if (message != "")
//             fmsPrint("%s", message.c_str());
//     }
// }

////////////////////////////////////////////////////////////////////////////////

#define checkAndReturn(condition, message) \
    if (!(condition))                      \
    {                                      \
        fmsError(message);                 \
        return;                            \
    }                                      \
    (void)(0)

////////////////////////////////////////////////////////////////////////////////

#define checkAndReturnValue(condition, message, value) \
    if (!(condition))                                  \
    {                                                  \
        fmsError(message);                             \
        return value;                                  \
    }                                                  \
    (void)(0)

////////////////////////////////////////////////////////////////////////////////

template <typename T>
const T& inRange(const T& in, const T& min, const T& max)
{
    if (min > max)
        return in;

    if (in < min)
        return min;
    if (max < in)
        return max;

    return in;
}

////////////////////////////////////////////////////////////////////////////////

#define inRangeInt inRange<int>
#define inRangeDouble inRange<double>
#define inRangeFloat inRange<float>

////////////////////////////////////////////////////////////////////////////////

#define fmsPrint fmsPrintInternal
#define fmsPrint_ fmsPrintInternalNoEnd
#define fmsDev fmsPrint
#define fmsError fmsPrintInternal
#define fmsError_ fmsPrintInternalNoEnd

#define FMS_TODO(arg) fmsPrint_("Unpopulated Function: %s[%d]: %s %s", __FILE__, __LINE__, __FUNCTION__, arg)

////////////////////////////////////////////////////////////////////////////////
