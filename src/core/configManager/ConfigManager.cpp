// Copyright 2022 Divyanshu Goel.
#include "core/configManager/ConfigManager.h"

#include "core/configManager/configParser/ConfigParserXML.h"

////////////////////////////////////////////////////////////////////////////////

crConfigManager::crConfigManager(const crFilePath& filePath)
    : mFilePath(filePath)
{
}

////////////////////////////////////////////////////////////////////////////////

crConfigManager::~crConfigManager()
{
}

////////////////////////////////////////////////////////////////////////////////

void crConfigManager::readFromFile(const crFilePath& filePath)
{
    const auto& aref = getInstance();
    if (!aref->mRead)
    {
        aref->mFilePath = filePath;
        auto ext = aref->mFilePath.getExtension();
        if (crUtils::iequals(ext, "xml"))
            aref->mConfigReader = std::make_shared<crConfigParserXML>(filePath);
        else
        {
            fmsError_("Please check input file. The file provided is: %s", aref->mFilePath.get().c_str());
            return;
        }

        bool success = aref->mConfigReader->readData();
        if (success)
        {
            aref->mConfig = aref->mConfigReader->config();
            if (aref->mConfig != nullptr)
                aref->mRead = true;
        }
        else
        {
            aref->mConfig.reset();
            aref->mConfig = nullptr;
        }
    }
    else
    {
        fmsError("ConfigManager reading Twice");
    }
}

////////////////////////////////////////////////////////////////////////////////

void crConfigManager::print()
{
    const auto& aref = getInstance();
    if (aref->mConfig != nullptr)
        aref->mConfig->print();
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigManager::get(std::string& out, const std::string& name)
{
    const auto& aref = getInstance();
    out = aref->get(name);
    if (out.size() == 0)
        return false;
    else
        return true;
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigManager::get(fmsRP<crConfig>& out, const std::string& name)
{
    const auto& aref = getInstance();
    out = aref->getConfig(name);
    if (out == nullptr)
        return false;
    else
        return true;
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigManager::available()
{
    const auto& aref = getInstance();
    return aref->mRead;
}

////////////////////////////////////////////////////////////////////////////////

std::string crConfigManager::get(const std::string& name)
{
    const auto& aref = getInstance();
    if (aref->mConfig != nullptr)
        return aref->mConfig->find(name);
    else
        return "";
}

////////////////////////////////////////////////////////////////////////////////

fmsSP<crConfig> crConfigManager::getConfig(const std::string& name)
{
    const auto& aref = getInstance();
    if (aref->mConfig != nullptr)
        return aref->mConfig->findConfig(name);
    else
        return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void crConfigManager::reset(const crFilePath& filePath)
{
    const auto& aref = getInstance();
    aref->mRead = false;
    if (aref->mConfig != nullptr)
    {
        aref->mConfig.reset();
        aref->mConfig = nullptr;
    }
    aref->readFromFile(filePath);
}

////////////////////////////////////////////////////////////////////////////////
