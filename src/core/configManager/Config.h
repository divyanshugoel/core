// Copyright 2022 Divyanshu Goel.
#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>

#include "core/configManager/ConfigElement.h"
#include "core/core/CoreDetail.h"
#include "core/core/Memory.h"
#include "core/file/FilePath.h"

#define MAX_CONFIG_ELEMENTS 50
#define MAX_CONFIG_DEPTH 10

////////////////////////////////////////////////////////////////////////////////
// This file defines a a way to store the config as a single value.

struct iequalsCmp
{
    // case-independent (ci) compare_less binary function
    struct nocaseCompare
    {
        bool operator()(const unsigned char& c1, const unsigned char& c2) const
        {
            return tolower(c1) < tolower(c2);
        }
    };
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), // source range
                                            rhs.begin(), rhs.end(), // dest range
                                            nocaseCompare());
    }
};

class crConfig
{
    typedef std::map<std::string, fmsSP<crConfig>, iequalsCmp> configMap;
    typedef std::map<std::string, fmsSP<crConfigElement>, iequalsCmp> configElementMap;

public:
    // Constructor.
    crConfig(const std::string& name, const std::string& description = "");
    crConfig(const fmsSP<crConfig>& parent = nullptr);
    crConfig(const fmsRP<crConfig>& parent);

    // Set the name.
    void name(const std::string& value);
    // Add the element.
    void addElement(const std::string& name, const std::string& value) noexcept;
    // Remove the element.
    void removeElement(const std::string& name) noexcept;
    // Add a sub config.
    void addSubConfig(const fmsSP<crConfig>& subConfig);
    // Remove a sub config.
    // It is preferred if you provide the full path.
    // If a split path is not provided then all instance are removed.
    void removeSubConfig(const std::string& name);
    // Add a description for this sub config.
    void description(const std::string& description);
    // Print all the values.
    void print(int spacing = 0) noexcept;

    // Return the value.
    const std::string& name() const noexcept;
    // Return the depth.
    const int& depth() const noexcept;
    // Find the value in this config space and sub spaces.
    // This searches by slash separated values.
    std::string find(const std::string& name);
    // Find the subconfig in this config space and sub spaces.
    // This searches by slash separated values.
    fmsSP<crConfig> findConfig(const std::string& name);
    // Return all the sub-Configs.
    const configMap& subConfig() const noexcept;

private:
    // Internal implementation of find.
    fmsSP<crConfig> findConfigInternal(const std::string& name);
    // Internal implementation of find element.
    fmsSP<crConfigElement> findElementInternal(const std::string& name);
    fmsSP<crConfig> findConfigInternal(const fmsCollection<std::string>& names, int index);
    fmsSP<crConfigElement> findElementInternal(const fmsCollection<std::string>& names, int index);

    // Store the name of the config.
    std::string mName = "";
    // Store the description of the config.
    std::string mDescription = "";
    // Store the depth
    int mDepth = 0;
    // Store the reference to the parent. Allows us to go back.
    fmsRP<crConfig> mParent = nullptr;
    // Store the child configs.
    configMap mSubConfigs;
    // Add the config elements at this level.
    configElementMap mSubConfigElements;
};

////////////////////////////////////////////////////////////////////////////////
