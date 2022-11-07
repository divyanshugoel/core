// Copyright 2022 Divyanshu Goel.
#pragma once

#include <cassert> // used for assert instances.
#include <cstddef> // For size_t, ptrdiff_t, etc.

#include <limits> // For std::numeric_limits
#include <memory> // for aliases
#include <optional> // for aliases
#include <type_traits> // used for adding removing const
#include <utility> // For std::forward, std::make_pair, etc.
#include <vector>

#include "core/configManager/ConfigManager.h"
#include "core/conversion/Convert.h"
#include "core/core/BoundedVariable.h"
#include "core/core/Color.h"
#include "core/core/CoreDetail.h"
#include "core/core/ExtendedSingleton.h"
#include "core/core/Memory.h"
#include "core/core/NamedTypeAddon.h"
#include "core/core/Profiler.h"
#include "core/core/SimpleSingleton.h"
#include "core/core/Time.h"
#include "core/core/Utils.h"
#include "core/core/Uuid.h"
#include "core/file/FilePath.h"
#include "core/logger/AgentLogger.h"
#include "core/logger/FleetLogger.h"
#include "core/math/Constants.h"
#include "core/math/Math.h"
#include "core/parameterManager/ParameterDef.h"
#include "core/parameterManager/ParameterInterface.h"
#include "core/parameterManager/ParameterSet.h"
#include <bits/stdc++.h>

// This portion of the code needs to be removed later.
#include "core/utils/GlobalStructs.h"
#include "core/utils/Utilities.h"

////////////////////////////////////////////////////////////////////////////////

/// for collection of shared pointers
template <typename T>
using fmsOpt = std::optional<T>;

////////////////////////////////////////////////////////////////////////////////
// Routines
////////////////////////////////////////////////////////////////////////////////

// #define checkAndReturn(condition, value) \
    // FMS_CHECK_AND_RETURN_IMPL(condition)

////////////////////////////////////////////////////////////////////////////////
// Indicates that a variable is unused (to avoid unused parameter warnings)
#define FMS_UNUSED(x) (void)(x)

////////////////////////////////////////////////////////////////////////////////
// Empty (no-op) statement
#define FMS_NO_OP() (void)(0)

////////////////////////////////////////////////////////////////////////////////
