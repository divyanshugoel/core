// Copyright 2022 Divyanshu Goel.
#pragma once

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

#include "core/core/Memory.h"
#include <bits/stdc++.h>
#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////////
//
namespace crUtils
{

// Return a collection on the basis of delimiter.
fmsCollection<std::string> split(const std::string& input, const char& delimiter);
// Trim character from the start and end of string.
std::string trim(const std::string& input, const char& character);
std::string lTrim(const std::string& input, const char& character);
std::string rTrim(const std::string& input, const char& character);

// Covert a int, float, double to a string with a given precision.
std::string toString(const bool& value, const int& precision = 0);
std::string toString(const int& value, const int& precision = 0);
std::string toString(const unsigned int& value, const int& precision = 0);
std::string toString(const double& value, const int& precision = 2);
std::string toString(const float& value, const int& precision = 2);
std::string toString(const std::string& value, const int& precision = 2);
std::string toString(const char& value, const int& precision = 2);
std::string toString(const glm::dvec3& point, const int& precision = 2);

template <typename T>
std::string toStringInternal(const T& value, const int& precision = 2)
{
    if (!std::is_arithmetic<T>::value)
        return "";

    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
};

// Case insensitive string compare.
bool iequals(const std::string& a, const std::string& b);

// Convert to lowercase.
std::string toLower(const std::string& a);
// Convert to uppercase.
std::string toUpper(const std::string& a);
// Repeat a string n no of times.
std::string repeat(const std::string& a, const int& n);

} // namespace crUtils
