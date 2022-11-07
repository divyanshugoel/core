// Copyright 2022 Divyanshu Goel.
#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "core/core/Core.h"

class grNode;
class grGraph;

////////////////////////////////////////////////////////////////////////////////
// Basic edge that goes into graph

class grEdge
{
public:
    grEdge() = default;
    // Set the edge between two nodes. The nodes may or may not exist the responsibilty lies with graph to manage that.
    grEdge(const fmsRP<grNode>& startNode, const fmsRP<grNode>& endNode, double weight, const std::string_view& name = "", bool isBidirectional = false, double length = 0);

    // Setters
    // Set the edge details.
    void name(const std::string_view& name);
    void direction(const bool& val);
    void weight(const double& w);
    void length(const double& l);
    void startNode(const fmsRP<grNode>& node);
    void endNode(const fmsRP<grNode>& node);
    void graph(const fmsRP<grGraph>& graph);
    void index(const int& val);

    // Getters
    // Get the edge details. IF more details are needed
    // in future or a different type of edge is needed
    // create a derived class
    const double& weight() const;
    const double& length() const;
    const std::string& name() const;
    const bool& isBidirectional() const;
    const int& index() const;
    // Return the start and end nodes.
    const fmsRP<grNode>& startNode() const;
    const fmsRP<grNode>& endNode() const;
    // Return the graph.
    const fmsRP<grGraph>& graph() const;

    // Print the details of the edge.
    void print() const;

    // Equality operator.
    bool operator==(const grEdge& B) const;

protected:
    // Start node for the edge.
    fmsRP<grNode> mStartNode;
    // End node for the edge.
    fmsRP<grNode> mEndNode;
    // Stores a pointer to the graph that edge is part of.
    fmsRP<grGraph> mGraph;
    // Parameters associated to edge.
    double mWeight{inf};
    double mLength{inf};
    // Index of the edge in the graph structure.
    int mIndex = 0;
    // Name of the edge.
    std::string mName;
    // Direction of the edge.
    bool mBidirectional{false};
};
