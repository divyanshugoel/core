// Copyright 2022 Divyanshu Goel.
#pragma once

#include <ctime>

#include <chrono>
#include <ratio>
#include <string>
#include <thread>

#include "core/core/Utils.h"

////////////////////////////////////////////////////////////////////////////////
// This is a base utility for providing time calculation for code
// the time is returned as the double value.

typedef std::chrono::time_point<std::chrono::system_clock> fmsTimePoint;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> fmsTimePointHRC;
typedef std::chrono::duration<double> fmsDuration;
typedef std::chrono::duration<double, std::milli> fmsDurationMS;
typedef std::chrono::duration<double, std::micro> fmsDurationUS;
typedef std::chrono::duration<double, std::nano> fmsDurationNS;

////////////////////////////////////////////////////////////////////////////////
// Set the ratio to 1000 for milliseconds, 1 for microseconds
inline void fmsSleep(const int& duration, const int& ratio = 1000)
{
    std::this_thread::sleep_for(std::chrono::microseconds(duration * ratio));
}

////////////////////////////////////////////////////////////////////////////////
// Set the ratio to 1000 for milliseconds, 1 for microseconds
inline void fmsSleep(const double& duration, const int& ratio = 1000)
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(duration * ratio)));
}

////////////////////////////////////////////////////////////////////////////////

void fmsLittleSleep(const int& microseconds, const int& ratio = 1000);

////////////////////////////////////////////////////////////////////////////////

inline fmsTimePointHRC getTimeNowHRC()
{
    return std::chrono::high_resolution_clock::now();
}

////////////////////////////////////////////////////////////////////////////////

inline fmsTimePoint getTimeNow()
{
    return std::chrono::system_clock::now();
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getDateStampStr(const fmsTimePoint& now)
{
    const auto& rawTime = std::chrono::system_clock::to_time_t(now);
    struct tm* timeInfo = std::localtime(&rawTime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y_%m_%d_%H_%M_%S", timeInfo);
    std::string dateStamp(buffer);
    return dateStamp;
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getDateStampStr()
{
    auto now = getTimeNow();
    return getDateStampStr(now);
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getTimeStampFormatStr(const fmsTimePoint& now)
{
    const auto& rawTime = std::chrono::system_clock::to_time_t(now);
    struct tm* timeInfo = std::localtime(&rawTime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H_%M_%S", timeInfo);
    std::string timeStamp(buffer);
    return timeStamp;
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getTimeStampFormatStr()
{
    auto now = getTimeNow();
    return getTimeStampFormatStr(now);
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getTimeNowStr(const fmsTimePointHRC& time)
{
    auto dat = time.time_since_epoch();
    double dTime = dat.count();
    dTime = dTime / 1E9;
    return crUtils::toString(dTime);
}

////////////////////////////////////////////////////////////////////////////////

inline std::string getTimeNowStr()
{
    auto time = getTimeNowHRC();
    return getTimeNowStr(time);
}

////////////////////////////////////////////////////////////////////////////////

inline double hoursPassed(const fmsTimePoint& timePoint, const fmsDuration& duration)
{
    std::chrono::duration<double, std::ratio<3600>> diff = getTimeNow() - timePoint;
    return diff.count();
}

////////////////////////////////////////////////////////////////////////////////

inline double daysPassed(const fmsTimePoint& timePoint, const fmsDuration& duration)
{
    return hoursPassed(timePoint, duration) / 24.0;
}

////////////////////////////////////////////////////////////////////////////////

inline bool isDurationPassed(const fmsTimePoint& timePoint, const fmsDuration& duration)
{
    auto diff = getTimeNow() - timePoint;
    return diff >= duration;
}

////////////////////////////////////////////////////////////////////////////////
