// Copyright 2022 Divyanshu Goel.
#include "graph/graph/shortestPath/Dijkstra.h"

#include "graph/graph/Graph.h"

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grDijkstra::impl(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode)
{
    fmsRPCollection<grNode> path;
    checkAndReturnValue(preCheck(graph, startNode, endNode), "Check the inputs", path);

    fmsRP<grNode> startNodePtr;
    fmsRP<grNode> endNodePtr;
    int startNodeLoc = graph->findNode(startNodePtr, startNode);
    int endNodeLoc = graph->findNode(endNodePtr, endNode);

    path.push_back(startNodePtr);
    // The algo starts from here
    // Initialization.
    mNodes = graph->nodes();
    // Allows for quick lookup of edge weight.
    graph->updateAdjacencyMatrix();
    size_t numNodes = mNodes.size();

    // Size -> No. of nodes in Nodes
    std::vector<double> dist(numNodes, inf);
    std::vector<int> visited(numNodes, 0);
    std::vector<int> parent(numNodes, 0);

    dist[startNodeLoc] = 0;
    parent[startNodeLoc] = -1;

    // Find shortest path for all vertices
    for (int count = 0; count < numNodes - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minimumDistance(dist, visited);
        // Mark the picked vertex as processed
        visited[u] = 1;
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int i = 0; i < numNodes; i++)
        {
            // Update dist[v] only if is not in visited, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            double cost = graph->getEdgeCost(u, i);
            if (!visited[i] && dist[u] != __DBL_MAX__ && dist[u] + cost < dist[i])
            {
                dist[i] = dist[u] + cost;
                parent[i] = u;
            }
        }
    }
    // Print the constructed distance array
    collatePath(path, parent, endNodePtr->index());
    // printSolution(path);
    return path;
}

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grDijkstra::impl(const grNode& startNode, const grNode& endNode)
{
    checkAndReturnValue(mGraph != nullptr, "Graph is empty", fmsRPCollection<grNode>());
    return (impl(mGraph, startNode.name(), endNode.name()));
}

////////////////////////////////////////////////////////////////////////////////

bool grDijkstra::preCheck(const fmsRP<grGraph>& graph, const std::string_view& startNode, const std::string_view& endNode)
{
    // Sanity Checks: If the graph is empty.
    checkAndReturnValue(graph != nullptr, "Graph is empty", false);

    // Sanity Checks: If the start/end node exists or not.
    fmsRP<grNode> startNodePtr;
    fmsRP<grNode> endNodePtr;
    int startNodeLoc = graph->findNode(startNodePtr, startNode);
    int endNodeLoc = graph->findNode(endNodePtr, endNode);
    checkAndReturnValue(startNodeLoc != -1, "Start Node not found", false);
    checkAndReturnValue(endNodeLoc != -1, "End Node not found", false);

    // Sanity Checks: If the start and end are same.
    checkAndReturnValue(startNodeLoc != endNodeLoc, "StartNode and End Node are same", false);
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void grDijkstra::collatePath(fmsRPCollection<grNode>& path, const std::vector<int>& parent, const int& index)
{
    if (parent[index] == -1)
        return;
    collatePath(path, parent, parent[index]);
    path.push_back(mNodes[index]);
}

////////////////////////////////////////////////////////////////////////////////

int grDijkstra::minimumDistance(const std::vector<double>& distance, const std::vector<int>& visited) const
{
    double minDistance = inf;
    int minIndex = -1;
    for (int i = 0; i < distance.size(); i++)
    {
        if (visited[i] == 0 && distance[i] <= minDistance)
        {
            minDistance = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}
////////////////////////////////////////////////////////////////////////////////

void grDijkstra::printSolution(const fmsRPCollection<grNode>& path) const
{
    fmsDev("PathSize: %ld", path.size());
    std::string pathStr = "";
    pathStr.append("Nodes: ");
    for (int i = 0; i < path.size(); i++)
    {
        pathStr.append(path[i]->name().c_str());
        if (i != path.size() - 1)
            pathStr.append(" --> ");
    }
    fmsDev("%s", pathStr.c_str());
}

////////////////////////////////////////////////////////////////////////////////
