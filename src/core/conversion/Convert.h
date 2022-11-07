// Copyright 2022 Divyanshu Goel.
#pragma once

#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////////////////////////

// Conversion b/w types
// Convert to int.
int toInt(const std::string& value);
// Convert to double.
double toDouble(const std::string& value);
// Convert to float.
float toFloat(const std::string& value);
// Convert hex string to integer
int hexToInt(const std::string& value);
// Convert uint8_t value to hexadecimal
std::string toHexString(const uint8_t& input);
std::string toHexString(const unsigned char& input);
