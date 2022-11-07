// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>

#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////////
// Higher-level type aliases
////////////////////////////////////////////////////////////////////////////////

/// for color
using fmsColor = std::string;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

////////////////////////////////////////////////////////////////////////////////
// Provides a way to specify the color. This is rgba format.

class crColor
{
public:
    crColor(const glm::dvec3& color);
    crColor(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& alpha = 255);
    // Utility functions.
    crColor invert();
    // Functions to convert color from rgb to other formats.
    // HSV
    // GRAY
    // LAB
    // BGR
    // HLS
    // LUV
    // YUV
    //

    // Setters.
    void r(const uint8_t& red);
    void g(const uint8_t& green);
    void b(const uint8_t& blue);
    void a(const uint8_t& alpha);
    // Getters.
    const uint8_t& r();
    const uint8_t& g();
    const uint8_t& b();
    const uint8_t& a();

private:
    // Store the rgba elements
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};
