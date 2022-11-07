// Copyright 2022 Divyanshu Goel.
#include "core/conversion/Convert.h"

#include "core/core/CoreDetail.h"

////////////////////////////////////////////////////////////////////////////////

int toInt(const std::string& value)
{
    int returnValue = 0;
    try
    {
        returnValue = std::stoi(value);
    }
    catch (const std::invalid_argument& e)
    {
        fmsError("Invalid Input. Resetting value to 0.");
    }
    catch (const std::out_of_range& e)
    {
        fmsError("Out of Range Input. Setting value to Max.");
        returnValue = __INT_MAX__;
    }
    return returnValue;
}

////////////////////////////////////////////////////////////////////////////////

double toDouble(const std::string& value)
{
    double returnValue = 0;
    try
    {
        returnValue = std::stod(value);
    }
    catch (const std::invalid_argument& e)
    {
        fmsError("Invalid Input. Resetting value to 0.");
    }
    catch (const std::out_of_range& e)
    {
        fmsError("Out of Range Input. Setting value to Max.");
        returnValue = __DBL_MAX__;
    }
    return returnValue;
}

////////////////////////////////////////////////////////////////////////////////

float toFloat(const std::string& value)
{
    float returnValue = 0;
    try
    {
        returnValue = std::stof(value);
    }
    catch (const std::invalid_argument& e)
    {
        fmsError("Invalid Input. Resetting value to 0.");
    }
    catch (const std::out_of_range& e)
    {
        fmsError("Out of Range Input. Setting value to Max.");
        returnValue = __FLT_MAX__;
    }
    return returnValue;
}

////////////////////////////////////////////////////////////////////////////////

int hexToInt(const std::string& value)
{
    int returnValue = 0;
    try
    {
        returnValue = std::stoul(value, nullptr, 16);
    }
    catch (const std::invalid_argument& e)
    {
        fmsError("Invalid Input. Resetting value to 0.");
    }
    catch (const std::out_of_range& e)
    {
        fmsError("Out of Range Input. Setting value to Max.");
        returnValue = __INT_MAX__;
    }
    return returnValue;
}

////////////////////////////////////////////////////////////////////////////////

std::string toHexString(const int& input)
{
    std::string temp;
    static const char* digits = "0123456789ABCDEF";
    size_t indexA = input / 16;
    size_t indexB = input & 0x0f;
    temp = std::string(1, digits[indexA]) + digits[indexB];
    return temp;
}
////////////////////////////////////////////////////////////////////////////////

std::string toHexString(const unsigned char& input)
{
    std::string temp;
    static const char* digits = "0123456789ABCDEF";
    size_t indexA = input / 16;
    size_t indexB = input & 0x0f;
    temp = std::string(1, digits[indexA]) + digits[indexB];
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
