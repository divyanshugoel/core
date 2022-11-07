// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>
#include <memory>

#include "core/configManager/configParser/ConfigParser.h"
#include "core/core/CoreDetail.h"
#include "core/core/Memory.h"
#include "core/file/FilePath.h"
#include "core/file/tinyxml2.h"

////////////////////////////////////////////////////////////////////////////////
// Read the config element.

class crConfigParserXML : public crConfigParser
{
    using BaseType = crConfigParser;

public:
    // Constructor.
    crConfigParserXML(const crFilePath& path);
    ~crConfigParserXML() = default;
    // Compute the data.
    bool readData() override;

private:
    // Internal implementation of reading data.
    void readDataInternal(const tinyxml2::XMLElement* element, fmsSP<crConfig>& config, std::string data);

    // Print the parser info.
    void printDataInternal() override;

private:
    // Store the XMLDocument
    tinyxml2::XMLDocument mDoc;
};
