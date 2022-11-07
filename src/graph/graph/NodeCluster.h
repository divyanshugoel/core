// Copyright 2022 Divyanshu Goel.
#pragma once

#include "core/core/Core.h"

#include "graph/graph/Node.h"

////////////////////////////////////////////////////////////////////////////////
// Store a group of Nodes

class grNodeCluster
{
public:
    // Constructor
    grNodeCluster() = default;

    // Utility functions.
    // Add the nodes
    void addNode(const fmsRP<grNode>& node);
    // Remove the nodes
    void removeNode(const fmsRP<grNode>& node);
    // Find a node
    unsigned int findNode(const fmsRP<grNode>& node) const;

    // Setters
    // Set the graph.
    void graph(const fmsRP<grGraph>& graph);

protected:
    // Collection of the nodes pointer.
    fmsRPCollection<grNode> mNodes;
    // Graph this node is part of.
    fmsRP<grGraph> mGraph;
};
