// Copyright 2022 Divyanshu Goel.
#include "core/core/Profiler.h"

////////////////////////////////////////////////////////////////////////////////

crTimeProfiler::crTimeProfiler(bool useHighResolutionClock, std::string id_) : mId(id_)
{
    if (useHighResolutionClock)
    {
        mUseHighResolutionClock = true;
        mEpochHRC = getTimeNowHRC();
        mStartHRC = getTimeNowHRC();
    }
    else
    {
        mEpochSC = getTimeNow();
        mStartSC = getTimeNow();
    }
}

////////////////////////////////////////////////////////////////////////////////

crTimeProfiler::~crTimeProfiler()
{
}

////////////////////////////////////////////////////////////////////////////////

void crTimeProfiler::timerReset()
{
    if (mUseHighResolutionClock)
        mStartHRC = getTimeNowHRC();
    else
        mStartSC = getTimeNow();
}

////////////////////////////////////////////////////////////////////////////////

void crTimeProfiler::setTimerStart()
{
    if (mUseHighResolutionClock)
        mStartHRC = getTimeNowHRC();
    else
        mStartSC = getTimeNow();
}

////////////////////////////////////////////////////////////////////////////////

double crTimeProfiler::getTimeElapsedSinceStart()
{
    if (mUseHighResolutionClock)
    {
        mEndHRC = getTimeNowHRC();
        std::chrono::duration<double> elapsedDuration = mEndHRC - mStartHRC;
        return elapsedDuration.count();
    }
    else
    {
        mEndSC = getTimeNow();
        std::chrono::duration<double> elapsedDuration = mEndSC - mStartSC;
        return elapsedDuration.count();
    }

    //    elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);
}

////////////////////////////////////////////////////////////////////////////////

double crTimeProfiler::getTimeElapsedSinceEpoch()
{
    if (mUseHighResolutionClock)
    {
        mEndHRC = getTimeNowHRC();
        std::chrono::duration<double> elapsedDuration = mEndHRC - mEpochHRC;
        return elapsedDuration.count();
    }
    else
    {
        mEndSC = getTimeNow();
        std::chrono::duration<double> elapsedDuration = mEndSC - mEpochSC;

        return elapsedDuration.count();
    }
}

////////////////////////////////////////////////////////////////////////////////

void crTimeProfiler::printTimeSinceStart()
{
    if (mUseHighResolutionClock)
    {
        mEndHRC = getTimeNowHRC();
        std::chrono::duration<double> elapsedDuration = mEndHRC - mStartHRC;

        fmsPrint("[%s] Time Elapsed since start is : %f sec", mId.c_str(), elapsedDuration.count());
    }
    else
    {
        mEndSC = getTimeNow();
        std::chrono::duration<double> elapsedDuration = mEndSC - mStartSC;
        fmsPrint("[%s] Time Elapsed since start is : %f sec", mId.c_str(), elapsedDuration.count());
    }
}

////////////////////////////////////////////////////////////////////////////////

void crTimeProfiler::printTimeSinceEpoch()
{
    if (mUseHighResolutionClock)
    {
        mEndHRC = getTimeNowHRC();
        std::chrono::duration<double> elapsedDuration = mEndHRC - mEpochHRC;
        fmsPrint("[%s] Time Elapsed since start is : %f sec", mId.c_str(), elapsedDuration.count());
    }
    else
    {
        mEndSC = getTimeNow();
        std::chrono::duration<double> elapsedDuration = mEndSC - mEpochSC;
        fmsPrint("[%s] Time Elapsed since start is : %f sec", mId.c_str(), elapsedDuration.count());
    }
}

////////////////////////////////////////////////////////////////////////////////
