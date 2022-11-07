// Copyright 2022 Divyanshu Goel.
#pragma once

#include <ctime>

#include <iostream>
#include <string>

#include "core/core/Time.h"
#include "core/core/CoreDetail.h"

////////////////////////////////////////////////////////////////////////////////
// This is a base utility for providing time calculation for code
// the time is returned as the double value.

class crTimeProfiler
{
public:
    // Constructor
    crTimeProfiler(bool useHighResolutionClock = true, std::string id_ = "");
    ~crTimeProfiler();

    // Reset the timer.
    void timerReset();

    // Set the start of timer.
    void setTimerStart();

    // Returns time in milliseconds since the init of the code.
    // Returns double Time elapsed in milliseconds.
    double getTimeElapsedSinceEpoch();

    /**
     * @brief Returns time in milliseconds since the start or timer reset.
     * @return double Time elapsed in milliseconds.
     */
    double getTimeElapsedSinceStart();

    /**
     * @brief Print time from start.
     */
    void printTimeSinceStart();

    /**
     * @brief Print time from last epoch.
     */
    void printTimeSinceEpoch();

private:
    /// Stores the system clock for start, epoch and end.
    fmsTimePoint mStartSC, mEndSC, mEpochSC;
    /// Stores the high resolution clock for start, epoch and end.
    fmsTimePointHRC mStartHRC, mEndHRC, mEpochHRC;
    /// Flag to enable high resolution clock.
    bool mUseHighResolutionClock = true;
    // String ID.
    std::string mId;
};
