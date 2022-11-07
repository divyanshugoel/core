// Copyright 2022 Divyanshu Goel.
#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>

#include "core/core/Core.h"

#include "graph/graph/Edge.h"
#include "graph/graph/Node.h"

class grShortestPathBase;

////////////////////////////////////////////////////////////////////////////////
// Basic directed graph that has a set of nodes and edges.

class grGraph : public std::enable_shared_from_this<grGraph>
{
public:
    // Constructor
    grGraph();

    // Utility functions
    // Add the nodes.
    virtual void addNode(const grNode& node);
    virtual void addNode(const std::string_view& name, const fms::gePose& pose, const fms::grNodeType type = fms::grNodeType::NONE);

    // Remove the nodes.
    virtual void removeNode(const grNode& node);
    virtual void removeNode(const std::string& name);

    // Add the edge.
    void addEdge(const grEdge& edge);
    void addEdge(const std::string& startNode, const std::string& endNode, double weight, const std::string_view& name = "", bool isBidirectional_ = false, double length = 0);
    // Remove the edge.
    void removeEdge(const grEdge& edge);
    void removeEdge(const std::string& edgeName);
    void removeEdge(const std::string& startNode, const std::string& endNode);

    // Returns index of the node if it is found. Also updates the outNode.
    int findNode(fmsRP<grNode>& outNode, const grNode& node) const;
    int findNode(fmsRP<grNode>& outNode, const std::string_view& name) const;
    int findNode(const grNode& node) const;
    int findNode(const std::string_view& name) const;

    // Returns the index of the edge if it is found, otherwise returns -1.
    // Optionally, can be used to set the value.
    // Return location of the edge if it exists in the graph
    int findEdge(fmsRP<grEdge>& outEdge, const grEdge& edge) const;
    // Return if an edge exists between two given nodes on edge name search.
    int findEdge(fmsRP<grEdge>& outEdge, const std::string& edgeName) const;
    // Return if an edge exists between two given nodes on node search.
    int findEdge(fmsRP<grEdge>& outEdge, const grNode& startNode, const grNode& endNode) const;
    // Return if an edge exists between two given nodes on name search for start and end nodes.
    int findEdge(fmsRP<grEdge>& outEdge, const std::string& startNode, const std::string& endNode) const;

    // Find if an edge exists by edge.
    int findEdge(const grEdge& edge) const;
    // Find if an edge exists by edge name.
    int findEdge(const std::string& edgeName) const;
    // Find if an edge exists by start and end node.
    int findEdge(const grNode& startNode, const grNode& endNode) const;
    // Find if an edge exists by start and end node names.
    int findEdge(const std::string& startNode, const std::string& endNode) const;
    // Get edge cost by start and end node index.
    const double& getEdgeCost(const int& startNode, const int& endNode) const;

    void setShortestPathMethod(fmsSP<grShortestPathBase> method);
    fmsRPCollection<grNode> shortestPath(const grNode& startNode, const grNode& endNode);
    fmsRPCollection<grNode> shortestPath(const std::string& startNode, const std::string& endNode);

    virtual void print() const;
    virtual void printNodes() const;
    virtual void printNodesDetailed() const;
    virtual void printEdges() const;

    // Getters
    const fmsSPCollection<grNode>& nodes() const;
    const fmsSPCollection<grEdge>& edges() const;
    // Get the nearest node by euclidean distance.
    fmsRP<grNode> nearestNode(const fms::gePose& pose);
    // Adjacency list initialization
    void updateAdjacencyMatrix();
    // TODO(-) add plot function for visualization

protected:
    // Updates the index of the nodes.
    void updateIndexNodes();
    // Updates the index of the nodes.
    void updateIndexEdges();
    // Update the connectivity and degree for the nodes.
    virtual void addNodeNeighbors(const fmsRP<grEdge> edge);
    virtual void removeNodeNeighbors(const fmsRP<grEdge> edge);

    /// Store the nodes
    fmsSPCollection<grNode> mNodes;
    /// Store the edges
    fmsSPCollection<grEdge> mEdges;

private:
    // Dirty bit for adjacency matrix generation.
    bool mDirty = true;
    // shortest path implementation
    fmsSP<grShortestPathBase> mShortestPathMethod;
    // Adjacency graph
    fms2DCollection<double> mAdjacencyMatrix;
};
