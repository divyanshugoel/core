// Copyright 2022 Divyanshu Goel.
#include "core/configManager/Config.h"

////////////////////////////////////////////////////////////////////////////////

crConfig::crConfig(const std::string& name, const std::string& description)
    : mName(name), mDescription(description)
{
    mDepth = 0;
}

////////////////////////////////////////////////////////////////////////////////

crConfig::crConfig(const fmsSP<crConfig>& parent)
    : mParent(parent)
{
    if (mParent == nullptr)
        mDepth = 0;
    else
        mDepth = mParent->depth() + 1;
}

////////////////////////////////////////////////////////////////////////////////

crConfig::crConfig(const fmsRP<crConfig>& parent)
    : mParent(parent)
{
    if (mParent == nullptr)
        mDepth = 0;
    else
        mDepth = mParent->depth() + 1;
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::name(const std::string& inputValue)
{
    mName = inputValue;
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::addElement(const std::string& name, const std::string& value) noexcept
{
    if (mSubConfigElements.size() > MAX_CONFIG_ELEMENTS)
        fmsPrint("Max no of elements reached. Please change the config file");
    else
    {
        auto configElement = std::make_shared<crConfigElement>(name, value);
        mSubConfigElements.emplace(name, configElement);
    }
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::removeElement(const std::string& name) noexcept
{
    FMS_TODO("DG");
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::addSubConfig(const fmsSP<crConfig>& subConfig)
{
    if (mDepth > MAX_CONFIG_DEPTH)
        fmsPrint("Max depth reached for %s. Please change the config file", subConfig->name().c_str());
    else
        mSubConfigs.try_emplace(subConfig->name(), subConfig);
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::removeSubConfig(const std::string& name)
{
    // auto config = find(name);
    FMS_TODO("DG");
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::description(const std::string& str)
{
    mDescription = str;
}

////////////////////////////////////////////////////////////////////////////////

void crConfig::print(int spacing) noexcept
{
    if (mSubConfigElements.size() == 0 && mSubConfigs.size() == 0)
        return;
    std::string nameData = crUtils::toString(name());
    std::string spacer = crUtils::repeat(" ", 3 * (spacing - 1));

    fmsPrint_("%s [%s]", spacer.c_str(), nameData.c_str());
    for (const auto& element : mSubConfigElements)
        element.second->print(spacing);

    for (const auto& element : mSubConfigs)
        element.second->print(spacing + 1);
}

////////////////////////////////////////////////////////////////////////////////

const std::string& crConfig::name() const noexcept
{
    return mName;
}

////////////////////////////////////////////////////////////////////////////////

const int& crConfig::depth() const noexcept
{
    return mDepth;
}

////////////////////////////////////////////////////////////////////////////////

std::string crConfig::find(const std::string& name)
{
    auto elementFound = findElementInternal(name);
    if (elementFound != nullptr)
        return elementFound->value();
    else
        return "";
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfig> crConfig::findConfig(const std::string& name)
{
    return findConfigInternal(name);
}

////////////////////////////////////////////////////////////////////////////////

const std::map<std::string, fmsSP<crConfig>, iequalsCmp>& crConfig::subConfig() const noexcept
{
    return mSubConfigs;
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfig> crConfig::findConfigInternal(const std::string& name)
{
    // First element is not root.
    // Character separator is '/'
    // Add a  provision for :
    // - Character separator - ':'
    auto outName = crUtils::trim(name, '/');
    auto outNames = crUtils::split(outName, '/');
    return findConfigInternal(outNames, 0);
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfigElement> crConfig::findElementInternal(const std::string& name)
{
    // First element is not root.
    // Character separator is '/'
    // Add a  provision for :
    // - Character separator - ':'
    auto outName = crUtils::trim(name, '/');
    auto outNames = crUtils::split(outName, '/');
    return findElementInternal(outNames, 0);
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfig> crConfig::findConfigInternal(const fmsCollection<std::string>& names, int index)
{
    if (names.size() == 0 || index >= names.size() || (mSubConfigElements.size() == 0 && mSubConfigs.size() == 0))
        return nullptr;
    std::string toSearchFor = names.at(index);
    if (names.size() - index == 1)
    {
        auto elementFound = mSubConfigs.find(toSearchFor);
        if (elementFound != mSubConfigs.end())
            return elementFound->second;
        else
            return nullptr;
    }
    else
    {
        auto configFound = mSubConfigs.find(toSearchFor);
        if (configFound != mSubConfigs.end())
            return (configFound->second->findConfigInternal(names, index + 1));
        else
            return nullptr;
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfigElement> crConfig::findElementInternal(const fmsCollection<std::string>& names, int index)
{
    if (names.size() == 0 || index >= names.size() || (mSubConfigElements.size() == 0 && mSubConfigs.size() == 0))
        return nullptr;
    std::string toSearchFor = names.at(index);
    if (names.size() - index == 1)
    {
        auto elementFound = mSubConfigElements.find(toSearchFor);
        if (elementFound != mSubConfigElements.end())
            return elementFound->second;
        else
            return nullptr;
    }
    else
    {
        auto configFound = mSubConfigs.find(toSearchFor);
        if (configFound != mSubConfigs.end())
            return (configFound->second->findElementInternal(names, index + 1));
        else
            return nullptr;
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
