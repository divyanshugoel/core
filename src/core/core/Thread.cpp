// Copyright 2022 Divyanshu Goel.
#include "core/core/Thread.h"

////////////////////////////////////////////////////////////////////////////////

crThread::~crThread()
{
    close();
}

////////////////////////////////////////////////////////////////////////////////

void crThread::startThread()
{
    if (!mProcessKilled)
        mThread = std::make_shared<std::thread>(&crThread::exec, this);
}

////////////////////////////////////////////////////////////////////////////////

void crThread::exec()
{
    checkAndReturn(mFunctionToExecute != nullptr, "Callback is empty");
    // Run the loop till the acknowledgement.
    fmsTimePoint lastTime = getTimeNow();
    while (!mProcessKilled)
    {
        fmsTimePoint current = getTimeNow();
        fmsDurationMS elapsed = current - lastTime;
        lastTime = current;
        double diff = mDelayTime - elapsed.count();
        if (diff <= 0)
            diff = 1;

        // Execute the function.
        functionToExecute();
        // Calculate the delay time in ms.
        int delay = delayTime(diff);
        fmsSleep(delay);
    }
}

////////////////////////////////////////////////////////////////////////////////

void crThread::close()
{
    kill();
    fmsSleep(mDelayTime);
    if (mThread->joinable())
    {
        mThread->join();
    }
}

////////////////////////////////////////////////////////////////////////////////

void crThread::frequency(const unsigned int& freq)
{
    mDelayTime = fms::safeDivide(1000, freq);
}

////////////////////////////////////////////////////////////////////////////////

void crThread::tickType(const crThreadTick& type)
{
    mTickType = type;
}

////////////////////////////////////////////////////////////////////////////////

void crThread::setCallback(const crThreadCallback& callback)
{
    mFunctionToExecute = callback;
}

////////////////////////////////////////////////////////////////////////////////

const int& crThread::frequency()
{
    return fms::safeDivide(1000, mDelayTime);
}

////////////////////////////////////////////////////////////////////////////////

void crThread::kill()
{
    std::lock_guard<std::mutex> lock(mLifeMtx);
    mProcessKilled = true;
}

////////////////////////////////////////////////////////////////////////////////

void crThread::functionToExecute()
{
    checkAndReturn(mFunctionToExecute != nullptr, "Callback is empty");
    mFunctionToExecute();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int crThread::delayTime(const unsigned int& value)
{
    if (mTickType == crThreadTick::SIMPLE)
        return mDelayTime;
    else if (mTickType == crThreadTick::FIXED_FRAME)
        return value;
    else
        return mDelayTime;
}

////////////////////////////////////////////////////////////////////////////////
