// Copyright 2022 Divyanshu Goel.
#pragma once

#include "core/core/Core.h"
#include "mathematics/geometry/base/Pose.h"

#include "graph/graph/Graph.h"

////////////////////////////////////////////////////////////////////////////////
// Utilities for graph class

namespace fms
{
enum class grPathCostType
{
    LENGTH,
    WEIGHT,
    EUCLIDEAN
};

class grGraphUtils
{
public:
    // Path is given in order.
    static fmsCollection<fms::gePose> collatePoses(const fmsRPCollection<grNode>& path);
    // Path cost.
    static double getPathCost(const fmsRPCollection<grNode>& path, fms::grPathCostType mode = fms::grPathCostType::EUCLIDEAN);
    // Returns the pointer to the node in a graph searched by string if it exists.
    static fmsRP<grNode> getNode(const fmsRP<grGraph>& graph, const std::string& name);   

private:
    static double getPathCostLengthImpl(const fmsRPCollection<grNode>& path);
    static double getPathCostWeightImpl(const fmsRPCollection<grNode>& path);
    static double getPathCostEuclideanImpl(const fmsRPCollection<grNode>& path);
};

} // namespace fms
