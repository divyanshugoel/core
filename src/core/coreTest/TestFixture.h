// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>

#include "gtest/gtest.h"

#define fmsTest TEST_F

class fmsTestFixture : public ::testing::Test
{
public:
    // Constructor.
    fmsTestFixture()
    {
    }
    // Destructor.
    ~fmsTestFixture()
    {
    }

protected:
    // Setup for the test fixture.
    void SetUp() override
    {
    }

    // Clear for the test fixture.
    void TearDown() override
    {
    }

    // Stores the messages since the failure.
    std::string failureMessages;
};
