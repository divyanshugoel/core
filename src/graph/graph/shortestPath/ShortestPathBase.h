// Copyright 2022 Divyanshu Goel.
#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "core/core/Core.h"

class grGraph;
class grNode;

////////////////////////////////////////////////////////////////////////////////
// Returns the shortest Path, could be overloaded to use different methods.

class grShortestPathBase
{
public:
    // Creates the abstract for shortest path method.
    virtual fmsRPCollection<grNode> impl(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode) = 0;
    // Wrapper to shorten the call.
    virtual fmsRPCollection<grNode> impl(const grNode& startNode, const grNode& endNode) = 0;

protected:
    fmsRP<grGraph> mGraph;
};
