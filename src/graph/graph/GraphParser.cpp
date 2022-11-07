// Copyright 2022 Divyanshu Goel.
#include "graph/graph/GraphParser.h"
#include "graph/graph/Graph.h"
#include "mathematics/geometry/base/Pose.h"

////////////////////////////////////////////////////////////////////////////////

void grGraphParser::read()
{
    // Validate the path
    if (!mFileName.isValid())
    {
        fmsError("File does not exist. Defaulting to backup file.");
        mFileName = crFilePath("scene/graph.map", crFileLocationType::ASSET);
    }
    mIfs.open(mFileName.get().c_str(), std::ifstream::in);
    mReader.parse(mIfs, mObj);
    // Read the details.
    readNodes();
    readConnections();
    close();
}

////////////////////////////////////////////////////////////////////////////////

void grGraphParser::close()
{
    if (mIfs.is_open())
        mIfs.close();
}

////////////////////////////////////////////////////////////////////////////////

void grGraphParser::readNodes()
{
    for (uint i = 0; i < mObj["nodes"].size(); i++)
    {
        auto node = readNode(i);
        mGraphData.addNode(node);
    }
}

////////////////////////////////////////////////////////////////////////////////

void grGraphParser::readConnections()
{
    for (uint i = 0; i < mObj["edges"].size(); i++)
    {
        auto localEdge = readConnection(i);
        mGraphData.addEdge(localEdge);
    }
}

////////////////////////////////////////////////////////////////////////////////

grNode grGraphParser::readNode(int index)
{
    grNode node;
    // Read the name of the Node.
    std::string name = mObj["nodes"][index]["name"].asString();
    std::string type = mObj["nodes"][index]["type"].asString();

    // Read the pose of the Node.
    fms::gePose pose;
    glm::dquat quat;
    pose.position.x = std::stod(mObj["nodes"][index]["pose"]["position"]["x"].asString());
    pose.position.y = std::stod(mObj["nodes"][index]["pose"]["position"]["y"].asString());
    pose.position.z = std::stod(mObj["nodes"][index]["pose"]["position"]["z"].asString());
    quat.x = std::stod(mObj["nodes"][index]["pose"]["orientation"]["x"].asString());
    quat.y = std::stod(mObj["nodes"][index]["pose"]["orientation"]["y"].asString());
    quat.z = std::stod(mObj["nodes"][index]["pose"]["orientation"]["z"].asString());
    quat.w = std::stod(mObj["nodes"][index]["pose"]["orientation"]["w"].asString());
    pose.orientation(quat);

    node.name(name);
    node.pose(pose);
    node.nodeType(type);

    return node;
}

////////////////////////////////////////////////////////////////////////////////

grEdge grGraphParser::readConnection(int index)
{
    std::string from = mObj["edges"][index]["from"].asString();
    std::string to = mObj["edges"][index]["to"].asString();
    std::string name = mObj["edges"][index]["name"].asString();
    std::string weightStr = mObj["edges"][index]["length"].asString();
    std::string directionStr = mObj["edges"][index]["isUniDirectional"].asString();
    bool bidirectional = true;
    double weight = INFINITY;
    bool invalidWeight = 0;

    if (directionStr == "true")
        bidirectional = false;
    fmsRP<grNode> firstNode, secondNode;
    int firstNodeIndex = mGraphData.findNode(firstNode, from);
    int secondNodeIndex = mGraphData.findNode(secondNode, to);
    try
    {
        weight = std::stod(weightStr);
    }
    catch (const std::invalid_argument &ia)
    {
        weight = INFINITY;
        invalidWeight = true;
    }
    if (firstNodeIndex != -1 && secondNodeIndex != -1)
    {
        double length = glm::distance(firstNode->pose().position, secondNode->pose().position);
        // if the weight is infinity
        if (weight == INFINITY && invalidWeight)
            weight = length;
        grEdge edge(firstNode, secondNode, weight, name, bidirectional, length);
        return edge;
    }
    else
    {
        fmsError("Invalid Nodes");
        grEdge edge;
        return edge;
    }
}

////////////////////////////////////////////////////////////////////////////////
