// Copyright 2022 Divyanshu Goel.
#include "core/core/Uuid.h"

////////////////////////////////////////////////////////////////////////////////

Uuid::Uuid()
{
}

////////////////////////////////////////////////////////////////////////////////

Uuid::Uuid(const Uuid& value)
{
    mValue = value.mValue;
    mCategory = value.mCategory;
    for (int i = 0; i < 16; i++)
    {
        mUuid[i] = value.mUuid[i];
    }
    mKey = value.mKey;
}

////////////////////////////////////////////////////////////////////////////////

Uuid::Uuid(const std::string& uuidString)
{
}

////////////////////////////////////////////////////////////////////////////////

Uuid::Uuid(const int& value)
{
    mValue = value;
}

////////////////////////////////////////////////////////////////////////////////

Uuid::Uuid(const uint8_t rawData[16])
{
    for (int i = 0; i < 16; i++)
    {
        mUuid[i] = rawData[i];
    }
}

////////////////////////////////////////////////////////////////////////////////

void Uuid::autoAssign(const std::string& category)
{
    setGenerator();
    mValue = mGen->getUniqueReadableValue(category);
    mKey = mGen->getUniqueKey();
    mCategory = category;
}

////////////////////////////////////////////////////////////////////////////////

void Uuid::setGenerator()
{
    if (!mGen)
        mGen = std::make_shared<UuidGenerator>();
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<UuidGenerator>& Uuid::getGenerator()
{
    return mGen;
}

////////////////////////////////////////////////////////////////////////////////

int Uuid::value() const
{
    return mValue;
}

////////////////////////////////////////////////////////////////////////////////

const std::string& Uuid::category() const
{
    return mCategory;
}

////////////////////////////////////////////////////////////////////////////////

std::string Uuid::toStr() const
{
    return crUtils::toString(mValue);
}

////////////////////////////////////////////////////////////////////////////////

std::string Uuid::toDashedStr() const
{
    return crUtils::toString(mValue);
}

////////////////////////////////////////////////////////////////////////////////

std::string Uuid::key() const
{
    return mKey;
}

////////////////////////////////////////////////////////////////////////////////

bool Uuid::isNull() const
{
    if (mValue == 0)
        return true;
    else
        return false;
}

////////////////////////////////////////////////////////////////////////////////

Uuid Uuid::null()
{
    return Uuid();
}

////////////////////////////////////////////////////////////////////////////////

void Uuid::print() const
{
    if (mCategory == "")
        fmsPrint_("Category : (null) %-12s Value : %-5d", "", mValue);
    else
        fmsPrint_("Category : %-19s Value : %-5d", mCategory.c_str(), mValue);
}

////////////////////////////////////////////////////////////////////////////////

const uint8_t* Uuid::getRawData() const noexcept
{
    return mUuid;
}

////////////////////////////////////////////////////////////////////////////////