// Copyright 2022 Divyanshu Goel.
#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "core/core/MacroExpansions.h"
#include "core/core/Memory.h"
#include "core/core/Time.h"
#include "core/math/Math.h"

enum class crThreadTick
{
    // Just a simple delay on the basis of frequency update.
    SIMPLE,
    // Time adjusted.
    FIXED_FRAME
    // There are others we need to add support.
};

////////////////////////////////////////////////////////////////////////////////
// Define a way to start thread and handle the frequency.
class crThread
{
    using crThreadCallback = std::function<void()>;

public:
    //  Constructor.
    crThread() = default;
    virtual ~crThread();

    // Utility
    // Start the thread.
    void startThread();
    // Execute the callback.
    void exec();
    // Close the thread.
    void close();

    // Setters.
    // Update the frequency in hertz.
    void frequency(const unsigned int& freq);
    // Set the update type.
    void tickType(const crThreadTick& type);
    // Set the callback function.
    void setCallback(const crThreadCallback& callback);

    // Getters.
    // Return the frequency.
    const int& frequency();

private:
    // Kill the thread.
    void kill();
    // Execute the function.
    void functionToExecute();
    // Calculate the delay time based on the type of tick.
    unsigned int delayTime(const unsigned int& value);

private:
    // Kill the process.
    std::atomic<bool> mProcessKilled{false};
    // Mutex for threaded version.
    std::mutex mLifeMtx;
    // Store the delay time for update loop.(in milliseconds)
    double mDelayTime = 1000;
    // Store the callback for the this thread.
    crThreadCallback mFunctionToExecute = nullptr;
    // Tick type
    crThreadTick mTickType;
    // Thread.
    fmsSP<std::thread> mThread;
};
