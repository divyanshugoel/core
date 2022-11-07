// Copyright 2022 Divyanshu Goel.
#include "graph/graph/Graph.h"

#include <algorithm>

#include "graph/graph/shortestPath/Dijkstra.h"
#include "graph/graph/shortestPath/NetworkFlow.h"

////////////////////////////////////////////////////////////////////////////////

grGraph::grGraph()
{
    mShortestPathMethod = std::make_shared<grDijkstra>();
};

////////////////////////////////////////////////////////////////////////////////

void grGraph::addNode(const grNode& node)
{
    if (findNode(node.name()) == -1)
    {
        mNodes.push_back(std::make_shared<grNode>(node));
        updateIndexNodes();
        mDirty = true;
    }
    else
        fmsDev("Node already exists");
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::addNode(const std::string_view& name, const fms::gePose& pose, const fms::grNodeType type)
{
    grNode nodeLocal;
    nodeLocal.name(name);
    nodeLocal.pose(pose);
    nodeLocal.nodeType(type);
    nodeLocal.index(mNodes.size());
    nodeLocal.graph(this);
    addNode(nodeLocal);
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeNode(const grNode& node)
{
    removeNode(node.name());
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeNode(const std::string& name)
{
    // check if node exists if it does then remove it.
    fmsRP<grNode> node;
    if (findNode(node, name) == -1)
    {
        fmsDev("Node doesn't exist");
    }
    else
    {
        const auto outgoingNeighbors = node->outgoingNeighbors();
        const auto incomingNeighbors = node->incomingNeighbors();
        for (const auto& neighborNode : outgoingNeighbors)
        {
            fmsDev("Removing connected edge: %s->%s", name.c_str(), neighborNode->name().c_str());
            removeEdge(name, neighborNode->name());
        }

        for (const auto& neighborNode : incomingNeighbors)
        {
            fmsDev("Removing connected edge: %s->%s", neighborNode->name().c_str(), name.c_str());
            removeEdge(neighborNode->name(), name);
        }
        // Remove the node after all the connecting edges are removed
        mNodes.erase(mNodes.begin() + node->index());
        mDirty = true;
        updateIndexNodes();
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::addEdge(const grEdge& edge)
{
    // TODO(-) check for all the conditions
    if (findEdge(edge) == -1)
    {
        // check the validity of the mNodes for the edge
        // ensure that they exist.
        auto startNode = edge.startNode();
        auto endNode = edge.endNode();
        if (findNode(startNode->name()) == -1 || findNode(endNode->name()) == -1)
        {
            fmsDev("One or more node does not exist");
        }
        else
        {
            // update degree, in-degree and out-degree of the corresponding nodes
            addNodeNeighbors(&edge);
            // add the edge to the vector.
            auto edgeLocal = std::make_shared<grEdge>(edge);
            edgeLocal->graph(this);
            mEdges.push_back(edgeLocal);
            mDirty = true;
        }
        updateIndexEdges();
    }
    else
    {
        fmsDev("Edge already exists");
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::addEdge(const std::string& startNode, const std::string& endNode, double weight, const std::string_view& name, bool isBidirectional, double length)
{
    fmsRP<grNode> firstNode, secondNode;

    if (findNode(firstNode, startNode) != -1 && findNode(secondNode, endNode) != -1)
    {
        grEdge edgeLocal(firstNode, secondNode, weight, name, isBidirectional, length);
        edgeLocal.graph(this);
        addEdge(edgeLocal);
    }
    else
    {
        fmsDev("Unable to find nodes in the graph");
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeEdge(const grEdge& edge)
{
    fmsRP<grEdge> edgeLocal;
    int index = findEdge(edgeLocal, edge);
    if (index != -1)
    {
        // Remove any mentions of this edge
        removeNodeNeighbors(edgeLocal);
        mEdges.erase(mEdges.begin() + index);
        updateIndexEdges();
        mDirty = true;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeEdge(const std::string& edgeName)
{
    fmsRP<grEdge> result;
    auto edgeIndex = findEdge(result, edgeName);
    if (edgeIndex != -1)
    {
        // Remove any mentions of this edge
        removeNodeNeighbors(result);
        mEdges.erase(mEdges.begin() + edgeIndex);
        updateIndexEdges();
        mDirty = true;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeEdge(const std::string& startNode, const std::string& endNode)
{
    fmsRP<grEdge> result;
    auto edgeIndex = findEdge(result, startNode, endNode);
    if (edgeIndex != -1)
    {
        // Remove any mentions of this edge.
        removeNodeNeighbors(result);
        mEdges.erase(mEdges.begin() + edgeIndex);
        updateIndexEdges();
        mDirty = true;
    }
}

//////////////////////////////////////////////////////////////////////////////

int grGraph::findNode(fmsRP<grNode>& outNode, const grNode& node) const
{
    return findNode(outNode, node.name());
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findNode(fmsRP<grNode>& outNode, const std::string_view& name) const
{
    int count = 0;
    for (const auto& it : mNodes)
    {
        if (it->name() == name)
        {
            outNode = it;
            return count;
        }
        count++;
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findNode(const grNode& node) const
{
    fmsRP<grNode> nodeVal;
    return findNode(nodeVal, node);
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findNode(const std::string_view& name) const
{
    fmsRP<grNode> nodeVal;
    return findNode(nodeVal, name);
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(fmsRP<grEdge>& outEdge, const grEdge& edge) const
{
    int count = 0;
    // Either the shared pointer itself is same or the name of the node can also be used as an option.
    for (const auto& it : mEdges)
    {
        if (*it == edge)
        {
            outEdge = it;
            return count;
        }
        count++;
    }
    outEdge = nullptr;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(fmsRP<grEdge>& outEdge, const std::string& edgeName) const
{
    int count = 0;
    for (const auto& it : mEdges)
    {
        if (it->name() == edgeName)
        {
            outEdge = it;
            return count;
        }
        count++;
    }
    outEdge = nullptr;
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(fmsRP<grEdge>& outEdge, const grNode& startNode, const grNode& endNode) const
{
    return findEdge(outEdge, startNode.name(), endNode.name());
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(fmsRP<grEdge>& outEdge, const std::string& startNode, const std::string& endNode) const
{
    int count = 0;
    // At this point check if the node name is same or not.
    for (const auto& it : mEdges)
    {
        if (it->startNode()->name() == startNode && it->endNode()->name() == endNode)
        {
            outEdge = it;
            return count;
        }
        if (it->isBidirectional() && it->startNode()->name() == endNode && it->endNode()->name() == startNode)
        {
            outEdge = it;
            return count;
        }
        count++;
    }
    outEdge = nullptr;
    // If the search was unsuccessful return -1.
    return -1;
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(const grEdge& edge) const
{
    fmsRP<grEdge> outEdge;
    return findEdge(outEdge, edge);
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(const std::string& edgeName) const
{
    fmsRP<grEdge> outEdge;
    return findEdge(outEdge, edgeName);
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(const grNode& startNode, const grNode& endNode) const
{
    fmsRP<grEdge> outEdge;
    return findEdge(outEdge, startNode, endNode);
}

////////////////////////////////////////////////////////////////////////////////

int grGraph::findEdge(const std::string& startNode, const std::string& endNode) const
{
    fmsRP<grEdge> outEdge;
    return findEdge(outEdge, startNode, endNode);
}

////////////////////////////////////////////////////////////////////////////////

const double& grGraph::getEdgeCost(const int& startNode, const int& endNode) const
{
    return mAdjacencyMatrix[startNode][endNode];
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::setShortestPathMethod(fmsSP<grShortestPathBase> method)
{
    checkAndReturn(method != nullptr, "Invalid method object");
    mShortestPathMethod = method;
}

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grGraph::shortestPath(const grNode& startNode, const grNode& endNode)
{
    if (mShortestPathMethod == nullptr)
        mShortestPathMethod = std::make_shared<grDijkstra>();

    return mShortestPathMethod->impl(this, startNode.name(), endNode.name());
}

////////////////////////////////////////////////////////////////////////////////

fmsRPCollection<grNode> grGraph::shortestPath(const std::string& startNode, const std::string& endNode)
{
    if (mShortestPathMethod == nullptr)
        mShortestPathMethod = std::make_shared<grDijkstra>();

    return mShortestPathMethod->impl(this, startNode, endNode);
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::print() const
{
    printNodesDetailed();
    printEdges();
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::printNodes() const
{
    fmsPrint("Nodes: ");
    fmsPrint("%s", std::string(75, '_').c_str());
    fmsPrint(" %-8s %-25s %-50s", "Index", "Node Name", "Position");
    fmsPrint("%s", std::string(75, '_').c_str());
    for (const auto& node : mNodes)
    {
        node->print();
    }
    fmsPrint("%s", std::string(75, '_').c_str());
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::printNodesDetailed() const
{
    fmsPrint("Nodes: ");
    fmsPrint("%s", std::string(150, '_').c_str());
    fmsPrint(" %-8s %-25s %-45s %-8s %-8s %-8s %-30s", "Index", "Node Name", "Position", "InDegree", "OutDegree", "Degree", "Neighbors");
    fmsPrint("%s", std::string(150, '_').c_str());
    for (const auto& node : mNodes)
    {
        node->printDetailed();
    }
    fmsPrint("%s", std::string(150, '_').c_str());
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::printEdges() const
{
    fmsPrint("Edges");
    fmsPrint("%s", std::string(100, '_').c_str());
    fmsPrint(" %-10s %-25s %-25s %-10s %-10s %-10s", "Index", "Start Node", "End Node", "Length", "Weight", "BiDirectional");
    fmsPrint("%s", std::string(100, '_').c_str());
    for (const auto& edge : mEdges)
    {
        edge->print();
    }
    fmsPrint("%s", std::string(100, '_').c_str());
}

////////////////////////////////////////////////////////////////////////////////

const fmsSPCollection<grNode>& grGraph::nodes() const
{
    return mNodes;
}

////////////////////////////////////////////////////////////////////////////////

const fmsSPCollection<grEdge>& grGraph::edges() const
{
    return mEdges;
}

////////////////////////////////////////////////////////////////////////////////

fmsRP<grNode> grGraph::nearestNode(const fms::gePose& pose)
{
    double min = inf;
    fmsRP<grNode> out;
    for (const auto& node : mNodes)
    {
        auto nodePose = node->pose();
        double dist = glm::distance(nodePose.position, pose.position);
        if (dist < min)
        {
            min = dist;
            out = node;
        }
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::updateIndexNodes()
{
    int count = 0;
    for (auto& it : mNodes)
    {
        it->index(count);
        count++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::updateIndexEdges()
{
    int count = 0;
    for (auto& it : mEdges)
    {
        it->index(count);
        count++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::updateAdjacencyMatrix()
{
    if (!mDirty)
        return;
    mAdjacencyMatrix.clear();
    for (int i = 0; i < mNodes.size(); i++)
    {
        std::vector<double> cost(mNodes.size(), inf);
        mAdjacencyMatrix.push_back(cost);
    }
    for (const auto& edge : mEdges)
    {
        int startNodeLoc = edge->startNode()->index();
        int endNodeLoc = edge->endNode()->index();
        mAdjacencyMatrix[startNodeLoc][endNodeLoc] = edge->weight();
        if (edge->isBidirectional())
            mAdjacencyMatrix[endNodeLoc][startNodeLoc] = edge->weight();
    }
    mDirty = false;
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::addNodeNeighbors(const fmsRP<grEdge> edge)
{
    auto startNode = edge->startNode();
    auto endNode = edge->endNode();
    startNode->addNeighbor(endNode);
    endNode->addNeighbor(startNode);
    startNode->addOutgoingNeighbor(endNode);
    endNode->addIncomingNeighbor(startNode);
    if (edge->isBidirectional())
    {
        endNode->addOutgoingNeighbor(startNode);
        startNode->addIncomingNeighbor(endNode);
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraph::removeNodeNeighbors(const fmsRP<grEdge> edge)
{
    auto startNode = edge->startNode();
    auto endNode = edge->endNode();
    startNode->removeNeighbor(endNode);
    endNode->removeNeighbor(startNode);
    startNode->removeOutgoingNeighbor(endNode);
    endNode->removeIncomingNeighbor(startNode);
    if (edge->isBidirectional())
    {
        endNode->removeOutgoingNeighbor(startNode);
        startNode->removeIncomingNeighbor(endNode);
    }
}

////////////////////////////////////////////////////////////////////////////////
