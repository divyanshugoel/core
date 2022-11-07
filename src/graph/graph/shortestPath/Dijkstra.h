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

class grDijkstra : public grShortestPathBase
{
public:
    // Implementation of the shortest path.
    fmsRPCollection<grNode> impl(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode) override;
    // Implementation of the shortest path.
    fmsRPCollection<grNode> impl(const grNode& startNode, const grNode& endNode) override;

private:
    // Sanity Checks: If the graph is empty. Start and end nodes are valid, or are same.
    bool preCheck(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode);
    // Collect the path.
    void collatePath(fmsRPCollection<grNode>& path, const std::vector<int>& parent, const int& index);
    // Get the minimum distance.
    int minimumDistance(const std::vector<double>& distance, const std::vector<int>& visited) const;
    // A utility function to print the constructed distance array, the solution.
    void printSolution(const fmsRPCollection<grNode>& path) const;

private:
    // Store the nodes.
    fmsSPCollection<grNode> mNodes;
};
