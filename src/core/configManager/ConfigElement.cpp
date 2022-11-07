// Copyright 2022 Divyanshu Goel.
#include "core/configManager/ConfigElement.h"

////////////////////////////////////////////////////////////////////////////////

crConfigElement::crConfigElement(const std::string& name, const std::string& value)
    : mName(name), mValue(value), mType(crDataType::STRING)
{
}

////////////////////////////////////////////////////////////////////////////////

void crConfigElement::value(const std::string& value) noexcept
{
    mValue = value;
}

////////////////////////////////////////////////////////////////////////////////

void crConfigElement::name(const std::string& name) noexcept
{
    mName = name;
}

////////////////////////////////////////////////////////////////////////////////

void crConfigElement::type(const crDataType& type) noexcept
{
    mType = type;
}

////////////////////////////////////////////////////////////////////////////////

const std::string& crConfigElement::value() const noexcept
{
    return mValue;
}

////////////////////////////////////////////////////////////////////////////////

const std::string& crConfigElement::name() const noexcept
{
    return mName;
}

////////////////////////////////////////////////////////////////////////////////

const crDataType& crConfigElement::type() const noexcept
{
    return mType;
}

////////////////////////////////////////////////////////////////////////////////

void crConfigElement::print(int spacing) noexcept
{
    std::string nameData = crUtils::toString(name());
    std::string valueData = crUtils::toString(value());
    std::string typeData = crUtils::toString(static_cast<int>(type()));
    std::string spacer = crUtils::repeat(" ", 3*spacing);
    spacer.append(nameData);
    fmsPrint_("%-30s %-25s", spacer.c_str(), valueData.c_str());
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigElement::operator==(const crConfigElement& B) const noexcept
{
    return mValue == B.mValue;
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigElement::operator==(const std::string& B) const noexcept
{
    return mValue == B;
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigElement::operator!=(const crConfigElement& B) const noexcept
{
    return !operator==(B);
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigElement::operator!=(const std::string& B) const noexcept
{
    return !operator==(B);
}

////////////////////////////////////////////////////////////////////////////////