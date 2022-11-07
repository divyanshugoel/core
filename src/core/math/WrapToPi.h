// Copyright 2022 Divyanshu Goel.
#pragma once

#include <limits>

#include "core/math/Constants.h"
#include <glm/glm.hpp>

// Floating-point modulo
// The result (the remainder) has same sign as the divisor.
// Similar to matlab's mod(); Not similar to fmod() -   Mod(-3,4)= 1   fmod(-3,4)= -3
template <typename T>
T mod(T x, T y)
{
    static_assert(!std::numeric_limits<T>::is_exact, "Mod: floating-point type expected");

    if (0. == y)
        return x;

    double m = x - y * floor(x / y);

    // handle boundary cases resulted from floating-point cut off:

    if (y > 0) // modulo range: [0..y)
    {
        if (m >= y) // Mod(-1e-16, 360): m= 360.
            return 0;

        if (m < 0)
        {
            if (y + m == y)
                return 0; // just in case...
            else
                return y + m; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14
        }
    }
    else // modulo range: (y..0]
    {
        if (m <= y) // Mod(1e-16              , -360.   ): m= -360.
            return 0;

        if (m > 0)
        {
            if (y + m == y)
                return 0; // just in case...
            else
                return y + m; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
        }
    }

    return m;
}

// wrap [rad] angle to [-PI..PI)
inline double wrapToPI(double fAng)
{
    return mod(fAng + PI, TWO_PI) - PI;
}

// wrap [rad] angle to [-PI..PI)
inline glm::dvec3 wrapToPI(glm::dvec3 ang)
{
    ang.x = wrapToPI(ang.x);
    ang.y = wrapToPI(ang.y);
    ang.z = wrapToPI(ang.z);
    return ang;
}

// wrap [rad] angle to [0..TWO_PI)
inline double wrapToTwoPI(double fAng)
{
    return mod(fAng, TWO_PI);
}

// wrap [rad] angle to [-PI..PI)
inline glm::dvec3 wrapToTwoPI(glm::dvec3 ang)
{
    ang.x = wrapToTwoPI(ang.x);
    ang.y = wrapToTwoPI(ang.y);
    ang.z = wrapToTwoPI(ang.z);
    return ang;
}

// wrap [deg] angle to [-180..180)
inline double wrapToDegree180(double fAng)
{
    return mod(fAng + 180., 360.) - 180.;
}

// wrap [deg] angle to [0..360)
inline double wrapToDegree360(double fAng)
{
    return mod(fAng, 360.);
}
