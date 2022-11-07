// Copyright 2022 Divyanshu Goel.
#include "core/coreTest/TestMgr.h"

#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////

int fmsTestMgr::altMain(int argc_, char** argv_, fmsOpt<int> numRun)
{
    // getInstance()->argc = argc_;
    // getInstance()->argv = argv_;
    getInstance()->mNumRuns = numRun;
    return getInstance()->runTests(argc_, argv_);
}

////////////////////////////////////////////////////////////////////////////////

int fmsTestMgr::runTests(int argc_, char** argv_)
{
    auto& inst = getInstance();

    testing::InitGoogleTest(&argc_, argv_);

    return RUN_ALL_TESTS();
}
