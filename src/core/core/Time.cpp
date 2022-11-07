// Copyright 2022 Divyanshu Goel.
#include "core/core/Time.h"

////////////////////////////////////////////////////////////////////////////////

void fmsLittleSleep(const int& microseconds, const int& ratio)
{
    std::chrono::microseconds us{microseconds * ratio};
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do
    {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}

////////////////////////////////////////////////////////////////////////////////
