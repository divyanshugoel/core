// Copyright 2022 Divyanshu Goel.
#include <string> // For converting integer to string

#include "core//parameterManager/ParameterDef.h"
#include "core/core/Core.h"
#include "core/coreTest/TestFixture.h"

////////////////////////////////////////////////////////////////////////////////

class ParamManagerTest : public fmsTestFixture
{
public:
    ParamManagerTest()
    {
    }

protected:
};

////////////////////////////////////////////////////////////////////////////////
//  Parameter Manager test
///////////////////////////////////////////////////////////////////////////////
//  Number of tests: 2
//
// Test description:
//
//  Test No: 1 - TestParameterManagerGlobal
//     Description: Check for the element in the global scope.
//          1. Insertion.
//          2. Deletion.
//          3. Finding.
//          4. Link a local variable.
//          5. Get all the variables and check.
//
//  Test No: 2 - TestParameterManagerLocal
//     Description: Check for the element in the local scope.
//          1. Insertion.
//          2. Deletion.
//          3. Finding.
//          4. Link a local variable.
//          5. Get all the variables and check.
//

////////////////////////////////////////////////////////////
// Test No: 1 - Check for the element in the global scope.

fmsTest(ParamManagerTest, TestParameterManagerGlobal)
{
}

////////////////////////////////////////////////////////////
// Test No: 2 - Check for the element in the local scope.

fmsTest(ParamManagerTest, TestParameterManagerLocal)
{
}
