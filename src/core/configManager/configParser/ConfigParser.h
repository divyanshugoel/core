// Copyright 2022 Divyanshu Goel.
#pragma once

#include "core/configManager/Config.h"
#include "core/configManager/configParser/ConfigParserTypes.h"
#include "core/core/CoreDetail.h"
#include "core/core/Memory.h"
#include "core/file/FilePath.h"

////////////////////////////////////////////////////////////////////////////////
// Read/Write the config element.

class crConfigParser
{
public:
    // Constructor.
    crConfigParser(const crFilePath& path);
    // Print File Data.
    void printData();
    // Return the config.
    const fmsSP<crConfig>& config() const;
    // Read from file.
    virtual bool readData() = 0;

protected:
    // Print the parser info.
    virtual void printDataInternal() = 0;

protected:
    // Store the file path.
    crFilePath mPath;
    // Store the config
    fmsSP<crConfig> mConfig = nullptr;
};
