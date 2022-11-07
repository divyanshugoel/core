// Copyright 2022 Divyanshu Goel.
#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "core/core/Core.h"
#include "glm/glm.hpp"
#include "mathematics/geometry/base/Pose.h"

class grGraph;
namespace fms
{
enum class grNodeType
{
    A,
    B
    NONE
};
} // namespace fms

////////////////////////////////////////////////////////////////////////////////
// Basic graph node that has a set of neighbors and edges.

class grNode
{
public:
    grNode() = default;
    grNode(const std::string& name, const fms::gePose& pose);

    // Setters.
    // Set the graph
    void graph(const fmsRP<grGraph>& graph);
    // Handle the name of the node.
    void name(const std::string_view& name);
    // Set the index of the node.
    void index(const int& index);
    // Set the enable/disable for the node.
    void enable();
    void disable();
    // Handle the color of the node. color need to replaced with rgb triplet of uint8_t
    void color(const fmsColor& color);
    // Position of the node
    void pose(const fms::gePose& pose);
    void nodeType(const fms::grNodeType& val);
    void nodeType(const std::string& type);

    // Neighbors of the given node, only existing nodes can be added,
    // these calls are more likely to be called when a graph is created.
    void addNeighbor(const fmsRP<grNode> neighborNode);
    void addIncomingNeighbor(const fmsRP<grNode> neighborNode);
    void addOutgoingNeighbor(const fmsRP<grNode> neighborNode);
    void removeNeighbor(const fmsRP<grNode> neighborNode);
    void removeIncomingNeighbor(const fmsRP<grNode> neighborNode);
    void removeOutgoingNeighbor(const fmsRP<grNode> neighborNode);

    // Getters
    // Returns the graph associated with the graph.
    const fmsRP<grGraph>& graph() const;

    // Get the details of the node.
    const std::string& name() const;
    const unsigned int& index() const;
    const fmsColor& color() const;
    const fms::gePose& pose() const;
    const fms::grNodeType& NodeType() const;

    // Get node details
    const unsigned int& inDegree() const;
    const unsigned int& outDegree() const;
    const unsigned int& degree() const;
    const double& weight() const;
    const double& length() const;

    // Neighbors fetch functions
    const fmsRPCollection<grNode>& neighbors() const;
    const fmsRPCollection<grNode>& incomingNeighbors() const;
    const fmsRPCollection<grNode>& outgoingNeighbors() const;

    // Additional search functions
    int findNeighbor(fmsRP<grNode>& outNode, const std::string& name);
    int findIncomingNeighbor(fmsRP<grNode>& outNode, const std::string& name);
    int findOutgoingNeighbor(fmsRP<grNode>& outNode, const std::string& name);

    int findNeighbor(const std::string& name);
    int findIncomingNeighbor(const std::string& name);
    int findOutgoingNeighbor(const std::string& name);

    // Print the details of the node in brief.
    virtual void print() const;
    // Print the details of the node.
    virtual void printDetailed() const;

    // Equality check.
    bool operator==(const grNode& B) const;

protected:
    // Store the neighbors of the node.
    fmsRPCollection<grNode> mNeighbors;
    // Store the incoming neighbor.
    fmsRPCollection<grNode> mIncomingNeighbors;
    // Store the outgoing neighbor.
    fmsRPCollection<grNode> mOutgoingNeighbors;

    // Graph this node is part of.
    fmsRP<grGraph> mGraph;
    // Incoming degree of the node.
    unsigned int mInDegree{0};
    // Outgoing degree of the node.
    unsigned int mOutDegree{0};
    // Degree of the node.
    unsigned int mDegree{0};
    // Index of the node in the graph.
    unsigned int mIndex{0};

    // Does weight, value of node makes sense. It might in some cases.
    double mWeight{inf};
    double mValue{inf};
    // Is the node enabled.
    bool mEnabled = true;
    // Name of the node.
    std::string mName;
    // Color of the node.
    fmsColor mColor;
    // Type of the node.
    fms::grNodeType mType = fms::grNodeType::NONE;
    // Specify if the node is going to be used in path generation.
    bool isTransitNode = true;
    // Pose of the node.
    fms::gePose mPose;
};
