// Copyright 2022 Divyanshu Goel.
#pragma once
#include <stdio.h>

#include <string>

#include "core/core/MacroExpansions.h"
#include "core/file/ConfigPath.h"
#include <sys/stat.h>

////////////////////////////////////////////////////////////////////////////////
// used to store absolute path. The input to be given as relative path from the
// source or install folder.

enum class crFileLocationType
{
    CONFIG,
    ASSET,
    ASSET_TEST,
    INSTALL,
    LOG,
    ABSOLUTE,
    SHADER,
    ROOT
};

class crFilePath
{
public:
    // Constructor
    crFilePath(const std::string& fileName = "", const crFileLocationType& type = crFileLocationType::CONFIG, bool computeExtension = false);
    // Constructor
    crFilePath(const char* fileName, const crFileLocationType& type = crFileLocationType::CONFIG, bool computeExtension = false);
    // Setters
    // Set the file Name, (Local File Name)
    void setFileName(const std::string& fileName, const std::string& prefix = "", bool computeExtension = false);
    void setFileName(const std::string& fileName, const crFileLocationType& type, bool computeExtension);
    // Set the filepath type
    void setPathType(const crFileLocationType& type);
    // Set the extension of the file.
    void setExtension(const std::string& extension);
    // Set the prefix of the file.
    void setPrefix(const std::string& prefix);
    // Check if the path is a directory.
    bool isDir() const;
    // Check if the path is a file.
    bool isFile() const;

    // Getters
    // By default returns the absolute path.
    std::string get() const;
    // By default returns the absolute path.
    const crFileLocationType& getPathType() const;
    // By default returns the relative path(inclusive of fileName).
    std::string getRelativePath() const;
    // Returns only the fileName.
    std::string getFileName() const;
    // Returns the extension.
    std::string getExtension() const;
    // Check if the path is valid.
    bool isValid() const;
    // Assign overload to convert
    const crFilePath& operator=(const std::string& str);
    crFilePath operator=(const char* name);

private:
    // Internal returns the extension.
    std::string getExtension(const crFileLocationType& type) const;
    // Internal implementation if the path is valid or not.
    void validate();
    // Internal implementation if the path is valid or not.
    bool exists() const;
    // Internal function to split filename into mutiple parts.
    // Presumes the first occurrence of .
    void splitFileName(const std::string& fileName);
    // Internal Check if there is an extension in the name.
    bool hasExtension(const std::string& name) const;
    // Internal Check if there is an localPath in the name.
    bool hasLocalPath(const std::string& name) const;
    // Internal Utility to remove extension.
    std::string removeExtension(const std::string& name) const;
    // Internal Utility to remove local path.
    std::string removeLocalPath(const std::string& name) const;
    // Internal Utility to get extension.
    std::string getExtension(const std::string& name) const;
    // Internal Utility to get local path if it exists.
    std::string getLocalPath(const std::string& name) const;

    // Set the file path variables.
    std::string mFilePathInstall = PROJECT_DIR_INSTALL;
    std::string mFilePathConfig = PROJECT_DIR_CONFIG;
    std::string mFilePathAsset = PROJECT_DIR_ASSETS;
    std::string mFilePathAssetTEST = PROJECT_DIR_ASSETS_TEST;
    std::string mFilePathLog = PROJECT_DIR_LOGS;
    std::string mFilePathShader = PROJECT_DIR_SHADER;
    std::string mFilePathRoot = PROJECT_DIR_ROOT;
    // File Name without prefix and extension.
    std::string mFileName = "";
    // Relative file Name
    std::string mFileNameFull = "";
    // Relative file Name
    std::string mLocalPath = "";
    // Absolute file paths
    std::string mFilePathAbsolute = "";
    // Extension of the file.
    std::string mExtension = "";
    // prefix to the file.
    std::string mPrefix = "";
    // Type of file path
    crFileLocationType mType;
    // Type of file path
    bool mDir = false;
    // Type of file path
    bool mValid = false;
    // Stores slash Win/Linux diff.
    char mSlash = '/';
};
