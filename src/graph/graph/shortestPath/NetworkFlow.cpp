// Copyright 2022 Divyanshu Goel.
#include "graph/graph/shortestPath/NetworkFlow.h"

#include "graph/graph/Graph.h"

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grNetworkFlow::impl(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode)
{
    fmsRPCollection<grNode> path;
    // Sanity Checks: If the graph is empty.
    checkAndReturnValue(graph != nullptr, "Graph is empty", path);

    // Sanity Checks: If the start/end node exists or not.
    fmsRP<grNode> startNodePtr;
    fmsRP<grNode> endNodePtr;
    int startNodeLoc = graph->findNode(startNodePtr, startNode);
    int endNodeLoc = graph->findNode(endNodePtr, endNode);
    checkAndReturnValue(startNodeLoc != -1, "Start Node not found", path);
    checkAndReturnValue(endNodeLoc != -1, "End Node not found", path);
    path.push_back(startNodePtr);
    // Sanity Checks: If the start and end are same.
    checkAndReturnValue(startNodeLoc != endNodeLoc, "StartNode and End Node are same", path);

    // The algo starts from here
    // Initialization.
    auto& nodes = graph->nodes();
    size_t numNodes = nodes.size();

    std::vector<double> label(numNodes, inf);
    std::vector<int> pathSequence(numNodes, -1);
    // Size -> No. of nodes in Nodes
    //TODO(dg) : double costs[numNodes]{0}; substitute by array
    double costs[100]{0};
    double visitedNodes[100]{0};
    // Size -> No. of nodes in Nodes
    // double visitedNodes[numNodes]{0};

    auto currentNode = startNodePtr;
    int currentIndex = startNodePtr->index();
    double currentCost = 0;
    int maxTries = 10000;
    while (true && maxTries >= 0)
    {
        double min = inf;
        visitedNodes[currentIndex] = 1;
        // If the current node has no neighbors then we cannot traverse.
        checkAndReturnValue(!currentNode->neighbors().empty(), "No path can be found", path);
        for (const auto& neighbor : currentNode->neighbors())
        {
            int index = neighbor->index();
            if (visitedNodes[index] == 0)
            {
                // Get the edge connecting current node and to be visited node.
                // Get the cost of the edge.
                fmsRP<grEdge> edge;
                auto edgeFound = graph->findEdge(edge, currentNode->name(), neighbor->name());
                int edgeCost = edge->weight();
                double cost = std::min(label[index], currentCost + edgeCost + costs[index]);
                if (cost != label[index])
                {
                    pathSequence[index] = currentIndex;
                    label[index] = cost;
                }
            }
        }
        for (int index = 0; index < label.size(); index++)
        {
            if (label[index] < min)
            {
                min = label[index];
                currentIndex = index;
                currentCost = min;
            }
        }
        label[currentIndex] = inf;
        if (currentIndex == endNodeLoc)
        {
            break;
        }
        maxTries--;
    }
    while (true)
    {
        if (currentIndex == startNodeLoc)
        {
            break;
        }
        fmsRP<grNode> nodeLink = nodes[currentIndex];
        path.insert(path.begin(), nodeLink);
        currentIndex = pathSequence[currentIndex];
    }
    return path;
}

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grNetworkFlow::impl(const grNode& startNode, const grNode& endNode)
{
    checkAndReturnValue(mGraph != nullptr, "Graph is empty", fmsRPCollection<grNode>());
    return (impl(mGraph, startNode.name(), endNode.name()));
}

////////////////////////////////////////////////////////////////////////////////
