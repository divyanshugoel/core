// Copyright 2022 Divyanshu Goel.
#pragma once

#include <memory>
#include <string>

#include "core/configManager/Config.h"
#include "core/configManager/configParser/ConfigParser.h"
#include "core/core/CoreDetail.h"
#include "core/core/Memory.h"
#include "core/core/SimpleSingleton.h"
#include "core/core/Utils.h"
#include "core/file/FilePath.h"

////////////////////////////////////////////////////////////////////////////////
// Config manager is a singleton class that stores the value

class crConfigManager : public crSingleton<crConfigManager>
{
    FMS_AUTO_SINGLETON(crConfigManager);

public:
    // Constructor
    crConfigManager(const crFilePath& filePath);
    crConfigManager() = default;
    ~crConfigManager();
    // Read config from file.
    void readFromFile(const crFilePath& filePath);
    // Save config to file.
    // Check if the Path exists.
    // - Create the directory
    // - Check if the file exists already.
    // - Verify with the default policy.
    // - Write or overwrite the file.
    void saveToFile(const crFilePath& filePath); // const crFilePolicy& policy);
    // Print all the  variables.
    void print();
    // Find an element.
    bool get(std::string& out, const std::string& name);
    bool get(fmsRP<crConfig>& out, const std::string& name);
    // Check if the file is read.
    bool available();

    std::string get(const std::string& name);
    fmsSP<crConfig> getConfig(const std::string& name);

    // Reset from a file.
    void reset(const crFilePath& filePath);

private:
    // Store the filePath of the config file.
    crFilePath mFilePath;
    // Store the configReader object.
    fmsSP<crConfigParser> mConfigReader;
    // Store the config.
    fmsSP<crConfig> mConfig = nullptr;
    // Ensure that the data is read only once.
    bool mRead = false;
};
