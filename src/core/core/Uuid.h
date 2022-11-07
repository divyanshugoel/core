// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>

#include "core/core/Utils.h"
#include "core/core/UuidGenerator.h"

////////////////////////////////////////////////////////////////////////////////
// Create a unique string
class Uuid
{

public:
    // Constructor
    Uuid();
    Uuid(const Uuid&);
    Uuid(const std::string& uuidString);
    Uuid(const int& value);
    Uuid(const uint8_t rawData[16]);

    // Initialize the value with a random value.
    void autoAssign(const std::string& category = "common");
    // Set the series generator.
    void setGenerator();
    // Set the series generator.
    fmsSP<UuidGenerator>& getGenerator();

    // Getters.
    int value() const;
    const std::string& category() const;
    std::string toStr() const;
    std::string toDashedStr() const;
    std::string key() const;

    // Returns true if the ID is zero.
    bool isNull() const;
    // Returns a null Uuid object.
    static Uuid null();
    // Returns a null Uuid object.
    void print() const;

    const uint8_t* getRawData() const noexcept;

    // Operators
    // TODO(dg) remove this.
    // Uuid& operator=(const Uuid& uuid) noexcept;
    // Uuid& operator=(const std::string& uuid) noexcept;
    // Uuid& operator= (const uint8_t* rawData) noexcept;

    // Comparison operators for boolean output
    // Equality : Inequality
    //  1. (BV == Type)
    //  2. (Type == BV)
    //  3. (BV == BV)

    bool operator!=(const Uuid& lhs) const
    {
        return !(*this == lhs);
    }
    bool operator!=(const uint16_t& lhs) const
    {
        return !(lhs == *this);
    }

    bool operator==(const Uuid& lhs) const
    {
        if (lhs.mValue == mValue || lhs.mKey == mKey && lhs.mCategory == mCategory)
            return true;
        else
            return false;
    }
    bool operator==(const int& lhs) const
    {
        if (lhs == mValue)
            return true;
        else
            return false;
    }
    friend bool operator==(const int& lhs, const Uuid& rhs)
    {
        return (lhs == rhs.mValue);
    }
    friend bool operator!=(const int& lhs, const Uuid& rhs)
    {
        return !(lhs == rhs);
    }
    friend bool operator!=(const Uuid& lhs, const int& rhs)
    {
        return !(rhs == lhs);
    }
    

    // Comparision :
    //  1. (Uuid <, >, <=, >= Type)
    //  2. (Type <, >, <=, >= Uuid)
    //  3. (Uuid <, >, <=, >= Uuid)
    bool operator<(const Uuid& lhs) const
    {
        if (lhs.mValue < mValue)
            return true;
        else
            return false;
    }
    bool operator<=(const Uuid& lhs) const
    {
        if (lhs.mValue <= mValue)
            return true;
        else
            return false;
    }
    bool operator>(const Uuid& lhs) const
    {
        if (lhs.mValue > mValue)
            return true;
        else
            return false;
    }
    bool operator>=(const Uuid& lhs) const
    {
        if (lhs.mValue >= mValue)
            return true;
        else
            return false;
    }

private:
    // Store the unique value.
    int mValue = 0;
    // Store the category.
    std::string mCategory;
    // Store the unique value in array.
    uint8_t mUuid[16];
    // Store the key.
    std::string mKey;
    // UUID Generator.
    fmsSP<UuidGenerator> mGen;
};
