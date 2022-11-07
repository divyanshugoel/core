// Copyright 2022 Divyanshu Goel.
#pragma once

#include "core/core/Core.h"
#include "core/core/SimpleSingleton.h"

class fmsTestMgr : public crSingleton<fmsTestMgr>
{
public:
    // fmsTestMgr(int &argc_, char **argv_): argc(argc_), argv(argv_) {};
    // Constructor.
    fmsTestMgr() = default;
    // Destructor.
    ~fmsTestMgr() = default;

public:
    // numRuns - Sets the number of times to run this suite of tests.
    static int altMain(int argc_, char** argv_, fmsOpt<int> numRun = std::nullopt);
    // Wrapper call to run the tests.
    int runTests(int argc_, char** argv_);

private:
    // Number of runs to do in a test.
    fmsOpt<int> mNumRuns;
};
