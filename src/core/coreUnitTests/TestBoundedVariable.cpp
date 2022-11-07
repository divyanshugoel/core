// Copyright 2022 Divyanshu Goel.
#include <string> // For converting integer to string

#include "core/core/Core.h"
#include "core/coreTest/TestFixture.h"

////////////////////////////////////////////////////////////////////////////////

class BoundedVariableTest : public fmsTestFixture
{
public:
    BoundedVariableTest()
    {
    }

protected:
    // Bounded variable
    crBoundedVariable<double> mDVar;
    // Bounded variable
    crBoundedVariable<int> mIVar;
    // Bounded variable
    crBoundedVariable<float> mFVar;
};

////////////////////////////////////////////////////////////////////////////////
//  Bounded Variable tests
///////////////////////////////////////////////////////////////////////////////
//  Number of tests: 2
//
// Test description:
//
//  Test No: 1 - TestBoundedVariable
//     Description: Check for when rate is infinite.
//          1. Assignment limit.
//          2. Arithmetic.
//          3. Equality.
//          3. Logical.
//
//  Test No: 2 - TestBoundedVariableRateLimited
//     Description: Check for when rate is finite.
//          1. Assignment limit.
//          2. Arithmetic.
//          3. Equality.
//          3. Logical.
//

////////////////////////////////////////////////////////////
// Test No: 1 - Check for when rate is infinite.

fmsTest(BoundedVariableTest, TestBoundedVariable)
{
}

////////////////////////////////////////////////////////////
// Test No: 2 - Check for when rate is finite.

fmsTest(BoundedVariableTest, TestBoundedVariableRateLimited)
{
}
