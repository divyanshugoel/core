// Copyright 2022 Divyanshu Goel.
#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include "core/core/CoreDetail.h"
#include "core/core/Memory.h"
#include "core/core/Utils.h"
#include "core/core/Types.h"
#include "core/file/FilePath.h"

////////////////////////////////////////////////////////////////////////////////
// This file defines a a way to store the config as a single value.
struct crConfigElement
{
public:
    // Constructor.
    crConfigElement() = default;
    crConfigElement(const std::string& name, const std::string& value);

    // Set the value.
    void value(const std::string& value) noexcept;
    // Set the value.
    void name(const std::string& name) noexcept;
    // Set the type.
    void type(const crDataType& type) noexcept;

    // Return the value.
    const std::string& value() const noexcept;
    // Return the value.
    const std::string& name() const noexcept;
    // Return the type.
    const crDataType& type() const noexcept;
    // Print the parameter
    void print(int spacing = 0) noexcept;

    // Operators.
    bool operator==(const crConfigElement& B) const noexcept;
    bool operator==(const std::string& B) const noexcept;
    bool operator!=(const crConfigElement& B) const noexcept;
    bool operator!=(const std::string& B) const noexcept;

private:
    // Store the default value of the parameter.
    std::string mName;
    // Value of the parameter.
    std::string mValue;
    // Value of the parameter.
    crDataType mType;
};

////////////////////////////////////////////////////////////////////////////////
