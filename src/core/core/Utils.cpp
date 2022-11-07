// Copyright 2022 Divyanshu Goel.
#include "core/core/Utils.h"

////////////////////////////////////////////////////////////////////////////////

fmsCollection<std::string> crUtils::split(const std::string& input, const char& delimiter)
{
    fmsCollection<std::string> temp;
    int lastIndex = -1;
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == delimiter)
        {
            auto str = input.substr(lastIndex + 1, i - lastIndex - 1);
            lastIndex = i;
            temp.push_back(str);
        }
        if (i == input.length() - 1)
        {
            auto str = input.substr(lastIndex + 1);
            temp.push_back(str);
        }
    }
    return temp;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::trim(const std::string& input, const char& character)
{
    std::string data = lTrim(input, character);
    data = rTrim(data, character);
    return data;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::lTrim(const std::string& input, const char& character)
{
    std::size_t count = 0;
    int length = input.length();
    std::string out = input;
    for (int i = 0; i < length; i++)
    {
        if (input[i] == character)
            continue;
        else
        {
            count = i;
            break;
        }
    }
    out = out.substr(count);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::rTrim(const std::string& input, const char& character)
{
    std::size_t count = 0;
    int length = input.length();
    std::string out = input;
    for (int i = length - 1; i > 0; i--)
    {
        if (input[i] == character)
            continue;
        else
        {
            count = i + 1;
            break;
        }
    }
    out = out.substr(0, count);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const bool& value, const int& precision)
{
    return crUtils::toStringInternal<bool>(value, precision);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const unsigned int& value, const int& precision)
{
    return crUtils::toStringInternal<unsigned int>(value, precision);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const int& value, const int& precision)
{
    return crUtils::toStringInternal<int>(value, precision);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const double& value, const int& precision)
{
    return crUtils::toStringInternal<double>(value, precision);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const float& value, const int& precision)
{
    return crUtils::toStringInternal<float>(value, precision);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const std::string& value, const int& precision)
{
    return value;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const char& value, const int& precision)
{
    return std::to_string(value);
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toString(const glm::dvec3& point, const int& precision)
{
    std::string msg;
    msg.append(crUtils::toString(point.x, precision));
    msg.append(",");
    msg.append(crUtils::toString(point.y, precision));
    msg.append(",");
    msg.append(crUtils::toString(point.z, precision));
    return msg;
}

////////////////////////////////////////////////////////////////////////////////

bool crUtils::iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) {
        return tolower(a) == tolower(b);
    });
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toLower(const std::string& input)
{
    std::string a = input;
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    return a;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::toUpper(const std::string& input)
{
    std::string a = input;
    std::transform(a.begin(), a.end(), a.begin(), ::toupper);
    return a;
}

////////////////////////////////////////////////////////////////////////////////

std::string crUtils::repeat(const std::string& a, const int& n)
{
    std::string temp = "";
    for (int i = 0; i < n; i++)
    {
        temp.append(a);
    }
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
