// Copyright 2022 Divyanshu Goel.
#include "graph/graph/Edge.h"

#include "graph/graph/Node.h"

////////////////////////////////////////////////////////////////////////////////

grEdge::grEdge(const fmsRP<grNode>& startNode, const fmsRP<grNode>& endNode, double weight, const std::string_view& name, bool isBidirectional, double length)
    : mStartNode(startNode), mEndNode(endNode), mName(name), mBidirectional(isBidirectional)
{
    this->weight(weight);
    this->length(length);
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::name(const std::string_view& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::direction(const bool& val)
{
    mBidirectional = val;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::weight(const double& w)
{
    checkAndReturn(w >= 0, "Invalid weight");
    mWeight = w;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::length(const double& l)
{
    checkAndReturn(l >= 0, "Invalid Length");
    mLength = l;
}
////////////////////////////////////////////////////////////////////////////////

void grEdge::startNode(const fmsRP<grNode>& node)
{
    checkAndReturn(node != nullptr, "Start node is Empty");
    mStartNode = node;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::endNode(const fmsRP<grNode>& node)
{
    checkAndReturn(node != nullptr, "End node is Empty");
    mEndNode = node;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::graph(const fmsRP<grGraph>& graph)
{
    checkAndReturn(graph != nullptr, "Graph node is Empty");
    mGraph = graph;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::index(const int& val)
{
    checkAndReturn(val >= 0, "Index should be non negative");
    mIndex = val;
}

////////////////////////////////////////////////////////////////////////////////

void grEdge::print() const
{
    // Check if the nodes are nullptr
    checkAndReturn(mStartNode != nullptr, "Start Node is empty");
    checkAndReturn(mEndNode != nullptr, "End Node is empty");
    // Print in the format
    // mStartNode mEndNode Weight Length isBiDirectional
    // TODO(dg): Replace this print call to output to stream and then the stream gets
    // flushed at periodic interval.
    std::string weightStr = crUtils::toString(mWeight);
    std::string lengthStr = crUtils::toString(mLength);
    std::string directionStr = crUtils::toString(mBidirectional);
    std::string indexStr = crUtils::toString(mIndex);
    fmsPrint(" %-10s %-25s %-25s %-10s %-10s %-10s", indexStr.c_str(), mStartNode->name().c_str(), mEndNode->name().c_str(), weightStr.c_str(), lengthStr.c_str(), directionStr.c_str());
}

////////////////////////////////////////////////////////////////////////////////

const double& grEdge::weight() const
{
    return mWeight;
}

////////////////////////////////////////////////////////////////////////////////

const double& grEdge::length() const
{
    return mLength;
}

////////////////////////////////////////////////////////////////////////////////

const std::string& grEdge::name() const
{
    return mName;
}

////////////////////////////////////////////////////////////////////////////////

const bool& grEdge::isBidirectional() const
{
    return mBidirectional;
}

////////////////////////////////////////////////////////////////////////////////

const int& grEdge::index() const
{
    return mIndex;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRP<grNode>& grEdge::startNode() const
{
    return mStartNode;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRP<grNode>& grEdge::endNode() const
{
    return mEndNode;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRP<grGraph>& grEdge::graph() const
{
    return mGraph;
}

////////////////////////////////////////////////////////////////////////////////

bool grEdge::operator==(const grEdge& B) const
{
    if (*mStartNode == *(B.mStartNode) && *mEndNode == *(B.mEndNode))
        return true;
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////////
