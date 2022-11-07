// Copyright 2022 Divyanshu Goel.
#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "core/core/Core.h"

#include "graph/graph/shortestPath/ShortestPathBase.h"

class grNode;
class grGraph;

////////////////////////////////////////////////////////////////////////////////
// Network flow based implementation for graph traversal.

class grNetworkFlow : public grShortestPathBase
{
public:
    // Implementation of the shortest path.
    fmsRPCollection<grNode> impl(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode) override;
    // Implementation of the shortest path.
    fmsRPCollection<grNode> impl(const grNode& startNode, const grNode& endNode) override;
};
