// Copyright 2022 Divyanshu Goel.
#pragma once

#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// This is a base utility for creating random numbers

class crRandomGenerator
{
public:
    // Constructor.
    crRandomGenerator();
    // Destructor.
    ~crRandomGenerator();

    // Returns a real random number in the range 0-1.
    double getRandomNumber();

    // Returns a integer random number in the range 0-100.
    int getRandomInteger(int limit = 100);

    // Set the seed for the random number generator.
    void setSeed(unsigned int seedVal);

    // Returns the seed for the random number generator.
    const unsigned int& getSeed() const;

private:
    // Seed value for the the random number generator.
    unsigned int mSeed;
};
