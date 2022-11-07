// Copyright 2022 Divyanshu Goel.
#include "core/file/FilePath.h"

#include <sys/stat.h>

////////////////////////////////////////////////////////////////////////////////

crFilePath::crFilePath(const std::string& fileName, const crFileLocationType& type, bool computeExtension)
{
    setFileName(fileName, type, computeExtension);
}

////////////////////////////////////////////////////////////////////////////////

crFilePath::crFilePath(const char* fileName, const crFileLocationType& type, bool computeExtension)
{
    std::string fileNameLocal(fileName);
    setPathType(type);
    setFileName(fileNameLocal, "", computeExtension);
    if (PLATFORM_NAME == "windows")
        mSlash = '\\';
    validate();
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::setFileName(const std::string& fileName, const crFileLocationType& type, bool computeExtension)
{
    setPathType(type);
    setFileName(fileName, "", computeExtension);
    if (PLATFORM_NAME == "windows")
        mSlash = '\\';
    validate();
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::setFileName(const std::string& fileName, const std::string& prefix, bool computeExtension)
{
    splitFileName(fileName);
    setPrefix(prefix);
    // mType =
    if (computeExtension)
        mExtension = getExtension(mType);
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::setPathType(const crFileLocationType& type)
{
    mType = type;
    switch (type)
    {
    case crFileLocationType::ASSET:
        mFilePathAbsolute = mFilePathAsset + mSlash;
        break;
    case crFileLocationType::ASSET_TEST:
        mFilePathAbsolute = mFilePathAssetTEST + mSlash;
        break;
    case crFileLocationType::CONFIG:
        mFilePathAbsolute = mFilePathConfig + mSlash;
        break;
    case crFileLocationType::INSTALL:
        mFilePathAbsolute = mFilePathInstall + mSlash;
        break;
    case crFileLocationType::LOG:
        mFilePathAbsolute = mFilePathLog + mSlash;
        break;
    case crFileLocationType::ROOT:
        mFilePathAbsolute = mFilePathRoot + mSlash;
        break;
    default:
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::setExtension(const std::string& extension)
{
    mExtension = extension;
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::setPrefix(const std::string& prefix)
{
    mPrefix = prefix;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::get() const
{
    return (mFilePathAbsolute + getFileName());
}

////////////////////////////////////////////////////////////////////////////////

const crFileLocationType& crFilePath::getPathType() const
{
    return mType;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getRelativePath() const
{
    return mLocalPath + getFileName();
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getFileName() const
{
    return mPrefix + mFileName + mExtension;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getExtension() const
{
    // Extension is designed to have the '.' in it.
    // So when we return we remove this dot.
    if (mExtension == "")
        return "";
    else
        return mExtension.substr(1);
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::isValid() const
{
    return mValid;
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::isDir() const
{
    bool validPath = exists();
    if (!validPath)
        return false;
    struct stat sb;
    if (stat(get().c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
        return true;
    else
        return false;
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::isFile() const
{
    bool validPath = exists();
    if (!validPath)
        return false;
    struct stat sb;
    if (stat(get().c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
        return false;
    else
        return true;
}

////////////////////////////////////////////////////////////////////////////////

const crFilePath& crFilePath::operator=(const std::string& str)
{
    setFileName(str, "", false);
    if (PLATFORM_NAME == "windows")
        mSlash = '\\';
    validate();
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

crFilePath crFilePath::operator=(const char* name)
{
    std::string str(name);
    setFileName(str, "", false);
    if (PLATFORM_NAME == "windows")
        mSlash = '\\';
    validate();
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getExtension(const crFileLocationType& type) const
{
    if (mExtension.length() > 0)
        return mExtension;

    switch (type)
    {
    case crFileLocationType::ASSET:
        return ".ast";
    case crFileLocationType::CONFIG:
        return ".cfg";
    case crFileLocationType::INSTALL:
        return "";
    case crFileLocationType::LOG:
        return ".log";
    case crFileLocationType::ROOT:
        return "";
    default:
        return "";
    }
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::validate()
{
    mValid = exists();
    mDir = isDir();
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::exists() const
{
    FMS_TODO("DG");
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void crFilePath::splitFileName(const std::string& fileName)
{
    if (hasExtension(fileName))
    {
        mFileName = removeExtension(fileName);
        mExtension = getExtension(fileName);
    }
    if (hasLocalPath(mFileName))
    {
        mFileName = removeLocalPath(fileName);
        mLocalPath = getLocalPath(fileName);
    }
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::hasExtension(const std::string& name) const
{
    std::size_t pos = name.find_first_of(".");
    return pos != std::string::npos;
}

////////////////////////////////////////////////////////////////////////////////

bool crFilePath::hasLocalPath(const std::string& name) const
{
    std::size_t pos = name.find_last_of(mSlash);
    return pos != std::string::npos;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::removeExtension(const std::string& name) const
{
    std::size_t pos = name.find_first_of(".");
    std::string outName;
    if (pos != std::string::npos)
        outName = name.substr(0, pos);
    else
        outName = name;
    return outName;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::removeLocalPath(const std::string& name) const
{
    std::size_t pos = name.find_last_of(mSlash);
    std::string outName = "";
    if (pos != std::string::npos)
        outName = name.substr(pos + 1);
    else
        outName = name;
    return outName;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getExtension(const std::string& name) const
{
    std::size_t pos = name.find_first_of(".");
    std::string outExt = "";
    if (pos != std::string::npos)
        outExt = name.substr(pos);
    else
        outExt = "";
    return outExt;
}

////////////////////////////////////////////////////////////////////////////////

std::string crFilePath::getLocalPath(const std::string& name) const
{
    std::size_t pos = name.find_last_of(mSlash);
    std::string outLocal = "";
    if (pos != std::string::npos)
        outLocal = name.substr(0, pos + 1);
    else
        outLocal = "";
    return outLocal;
}

////////////////////////////////////////////////////////////////////////////////
