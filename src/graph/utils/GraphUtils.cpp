// Copyright 2022 Divyanshu Goel.
#include "graph/utils/GraphUtils.h"

////////////////////////////////////////////////////////////////////////////////

fmsCollection<fms::gePose> fms::grGraphUtils::collatePoses(const fmsRPCollection<grNode>& path)
{
    fmsCollection<fms::gePose> poses;
    for (const auto& node : path)
        poses.push_back(node->pose());

    return poses;
}

////////////////////////////////////////////////////////////////////////////////

double fms::grGraphUtils::getPathCost(const fmsRPCollection<grNode>& path, fms::grPathCostType mode)
{
    if (mode == fms::grPathCostType::LENGTH)
        return getPathCostLengthImpl(path);
    if (mode == fms::grPathCostType::WEIGHT)
        return getPathCostWeightImpl(path);

    return getPathCostEuclideanImpl(path);
}

////////////////////////////////////////////////////////////////////////////////

fmsRP<grNode> fms::grGraphUtils::getNode(const fmsRP<grGraph>& graph, const std::string& name)
{
    checkAndReturnValue(graph != nullptr, "Graph is empty", nullptr);
    fmsRP<grNode> node;
    int index = graph->findNode(node, name);
    if (index == -1)
        return nullptr;
    else
        return node;
}

////////////////////////////////////////////////////////////////////////////////

double fms::grGraphUtils::getPathCostLengthImpl(const fmsRPCollection<grNode>& path)
{
    double cost = 0;
    for (int i = 0; i < path.size(); i++)
    {
        cost = cost + path[i]->length();
    }
    return cost;
}

////////////////////////////////////////////////////////////////////////////////

double fms::grGraphUtils::getPathCostWeightImpl(const fmsRPCollection<grNode>& path)
{
    double cost = 0;
    for (int i = 0; i < path.size(); i++)
    {
        cost = cost + path[i]->weight();
    }
    return cost;
}

////////////////////////////////////////////////////////////////////////////////

double fms::grGraphUtils::getPathCostEuclideanImpl(const fmsRPCollection<grNode>& path)
{
    double cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        auto nodeA = path[i]->pose().position;
        auto nodeB = path[i]->pose().position;
        auto nodeCost = glm::distance(nodeA, nodeB);
        cost = cost + nodeCost;
    }
    return cost;
}

////////////////////////////////////////////////////////////////////////////////
