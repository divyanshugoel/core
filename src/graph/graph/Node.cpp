// Copyright 2022 Divyanshu Goel.
#include "graph/graph/Node.h"

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

grNode::grNode(const std::string& name, const fms::gePose& pose)
    : mName(name), mPose(pose)
{
}

////////////////////////////////////////////////////////////////////////////////

void grNode::graph(const fmsRP<grGraph>& graph)
{
    checkAndReturn(graph != nullptr, "Graph is empty");
    mGraph = graph;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::name(const std::string_view& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::index(const int& index)
{
    if (index <= 0)
        mIndex = 0;
    else
        mIndex = index;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::enable()
{
    mEnabled = true;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::disable()
{
    mEnabled = false;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::color(const fmsColor& color)
{
    mColor = color;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::pose(const fms::gePose& pose)
{
    mPose = pose;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::nodeType(const fms::grNodeType& val)
{
    mType = val;
}

////////////////////////////////////////////////////////////////////////////////

void grNode::nodeType(const std::string& type)
{
    std::string copyType = type;
    fms::grNodeType nodeTypeLocal = fms::grNodeType::NONE;
    transform(copyType.begin(), copyType.end(), copyType.begin(), ::tolower);

    if (copyType == "pick")
        nodeTypeLocal = fms::grNodeType::PICK;
    if (copyType == "drop")
        nodeTypeLocal = fms::grNodeType::DROP;
    if (copyType == "wait")
        nodeTypeLocal = fms::grNodeType::WAIT;
    if (copyType == "charge")
        nodeTypeLocal = fms::grNodeType::CHARGE;
    if (copyType == "dock")
        nodeTypeLocal = fms::grNodeType::DOCK;
    if (copyType == "pre_dock" || copyType == "predock")
        nodeTypeLocal = fms::grNodeType::PRE_DOCK;
    if (copyType == "un_dock" || copyType == "undock")
        nodeTypeLocal = fms::grNodeType::UN_DOCK;
    if (copyType == "post_dock" || copyType == "postdock")
        nodeTypeLocal = fms::grNodeType::POST_DOCK;
    if (copyType == "none")
        nodeTypeLocal = fms::grNodeType::NONE;

    nodeType(nodeTypeLocal);
}

////////////////////////////////////////////////////////////////////////////////

void grNode::addNeighbor(const fmsRP<grNode> neighborNode)
{
    checkAndReturn(neighborNode != nullptr, "Node is empty");
    int isNeighborAlready = findNeighbor(neighborNode->name());
    if (isNeighborAlready == -1)
    {
        mNeighbors.push_back(neighborNode);
        mDegree++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grNode::addIncomingNeighbor(const fmsRP<grNode> neighborNode)
{
    checkAndReturn(neighborNode != nullptr, "Node is empty");
    int isNeighborAlready = findIncomingNeighbor(neighborNode->name());
    if (isNeighborAlready == -1)
    {
        mIncomingNeighbors.push_back(neighborNode);
        mInDegree++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grNode::addOutgoingNeighbor(fmsRP<grNode> neighborNode)
{
    checkAndReturn(neighborNode != nullptr, "Node is empty");
    int isNeighborAlready = findOutgoingNeighbor(neighborNode->name());
    if (isNeighborAlready == -1)
    {
        mOutgoingNeighbors.push_back(neighborNode);
        mOutDegree++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grNode::removeNeighbor(fmsRP<grNode> neighborNode)
{
    if (neighborNode == nullptr)
        return;
    else
    {
        int neighborIndex = findNeighbor(neighborNode->name());
        if (neighborIndex != -1)
        {
            mNeighbors.erase(mNeighbors.begin() + neighborIndex);
            mDegree--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void grNode::removeIncomingNeighbor(fmsRP<grNode> neighborNode)
{
    if (neighborNode == nullptr)
        return;
    else
    {
        int neighborIndex = findIncomingNeighbor(neighborNode->name());
        if (neighborIndex != -1)
        {
            mIncomingNeighbors.erase(mIncomingNeighbors.begin() + neighborIndex);
            mInDegree--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void grNode::removeOutgoingNeighbor(fmsRP<grNode> neighborNode)
{
    if (neighborNode == nullptr)
        return;
    else
    {
        int neighborIndex = findOutgoingNeighbor(neighborNode->name());
        if (neighborIndex != -1)
        {
            mOutgoingNeighbors.erase(mOutgoingNeighbors.begin() + neighborIndex);
            mOutDegree--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

const fmsRP<grGraph>& grNode::graph() const
{
    return mGraph;
}

////////////////////////////////////////////////////////////////////////////////

const std::string& grNode::name() const
{
    return mName;
}

////////////////////////////////////////////////////////////////////////////////

const unsigned int& grNode::index() const
{
    return mIndex;
}

////////////////////////////////////////////////////////////////////////////////

const fmsColor& grNode::color() const
{
    return mColor;
}

////////////////////////////////////////////////////////////////////////////////

const fms::gePose& grNode::pose() const
{
    return mPose;
}

////////////////////////////////////////////////////////////////////////////////

const fms::grNodeType& grNode::NodeType() const
{
    return mType;
}

////////////////////////////////////////////////////////////////////////////////

const unsigned int& grNode::inDegree() const
{
    return mInDegree;
}

////////////////////////////////////////////////////////////////////////////////

const unsigned int& grNode::outDegree() const
{
    return mOutDegree;
}

////////////////////////////////////////////////////////////////////////////////

const unsigned int& grNode::degree() const
{
    return mDegree;
}

////////////////////////////////////////////////////////////////////////////////

const double& grNode::weight() const
{
    return mWeight;
}

////////////////////////////////////////////////////////////////////////////////

const double& grNode::length() const
{
    return mValue;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRPCollection<grNode>& grNode::neighbors() const
{
    return mNeighbors;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRPCollection<grNode>& grNode::incomingNeighbors() const
{
    return mIncomingNeighbors;
}

////////////////////////////////////////////////////////////////////////////////

const fmsRPCollection<grNode>& grNode::outgoingNeighbors() const
{
    return mOutgoingNeighbors;
}
////////////////////////////////////////////////////////////////////////////////

int grNode::findNeighbor(fmsRP<grNode>& outNode, const std::string& name)
{
    int count = 0;
    for (auto it = mNeighbors.begin(); it < mNeighbors.end(); it++)
    {
        if ((*it)->name() == name)
        {
            outNode = *it;
            return count;
        }
        count++;
    }
    outNode = nullptr;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grNode::findIncomingNeighbor(fmsRP<grNode>& outNode, const std::string& name)
{
    int count = 0;
    for (auto it = mIncomingNeighbors.begin(); it < mIncomingNeighbors.end(); it++)
    {
        if ((*it)->name() == name)
        {
            outNode = *it;
            return count;
        }
    }
    outNode = nullptr;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grNode::findOutgoingNeighbor(fmsRP<grNode>& outNode, const std::string& name)
{
    int count = 0;
    for (auto it = mOutgoingNeighbors.begin(); it < mOutgoingNeighbors.end(); it++)
    {
        if ((*it)->name() == name)
        {
            outNode = *it;
            return count;
        }
    }
    outNode = nullptr;
    return -1;
}
////////////////////////////////////////////////////////////////////////////////

int grNode::findNeighbor(const std::string& name)
{
    fmsRP<grNode> node;
    return findNeighbor(node, name);
}
////////////////////////////////////////////////////////////////////////////////

int grNode::findIncomingNeighbor(const std::string& name)
{
    fmsRP<grNode> node;
    return findIncomingNeighbor(node, name);
}

////////////////////////////////////////////////////////////////////////////////

int grNode::findOutgoingNeighbor(const std::string& name)
{
    fmsRP<grNode> node;
    return findOutgoingNeighbor(node, name);
}

///////////////////////////////////////////////////////////////////////////////

void grNode::print() const
{
    std::string pos = "(";
    pos.append(crUtils::toString(mPose.position.x));
    pos.append(", ");
    pos.append(crUtils::toString(mPose.position.y));
    pos.append(", ");
    pos.append(crUtils::toString(mPose.position.z));
    pos.append(")");
    std::string indexStr = crUtils::toString(mIndex);
    fmsPrint(" %-8s %-25s %-25s", indexStr.c_str(), mName.c_str(), pos.c_str());
}

///////////////////////////////////////////////////////////////////////////////

void grNode::printDetailed() const
{
    std::string pos = "(";
    pos.append(crUtils::toString(mPose.position.x));
    pos.append(", ");
    pos.append(crUtils::toString(mPose.position.y));
    pos.append(", ");
    pos.append(crUtils::toString(mPose.position.z));
    pos.append(")");
    std::string inDegreeStr = crUtils::toString(mInDegree);
    std::string outDegreeStr = crUtils::toString(mOutDegree);
    std::string degreeStr = crUtils::toString(mDegree);
    std::string indexStr = crUtils::toString(mIndex);

    // Print all neighbors
    std::string neighborsStr = "";
    for (const auto& neighbor : mNeighbors)
    {
        neighborsStr.append(neighbor->name().c_str());
        if (neighbor != mNeighbors.back())
            neighborsStr.append(", ");
    }
    fmsPrint(" %-8s %-25s %-45s %-8s %-8s %-8s %-30s", indexStr.c_str(), mName.c_str(), pos.c_str(), inDegreeStr.c_str(), outDegreeStr.c_str(), degreeStr.c_str(), neighborsStr.c_str());
}

///////////////////////////////////////////////////////////////////////////////

bool grNode::operator==(const grNode& B) const
{
    // it is upto us if we want equality of both the conditions.
    // name should suffice i think.
    if (mName == B.mName && mPose == B.mPose && mType == B.mType)
        return true;
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////////
