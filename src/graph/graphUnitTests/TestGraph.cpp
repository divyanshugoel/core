
// Copyright 2022 Divyanshu Goel.
#include <ctime> // For finding the time of node creation

#include <string> // For converting integer to string

#include "core/core/Core.h"
#include "core/coreTest/TestFixture.h"
#include "glm/glm.hpp"
#include "mathematics/geometry/base/Pose.h"

#include "graph/graph/Graph.h"
#include "graph/graph/GraphParser.h"

////////////////////////////////////////////////////////////////////////////////

class graphTest : public fmsTestFixture
{
public:
    graphTest()
    {
        P0.position = glm::dvec3(0, 0, 0);
        P1.position = glm::dvec3(10, 0, 0);
        P2.position = glm::dvec3(0, 10, 0);
        P3.position = glm::dvec3(10, 10, 0);
    }

protected:
    fms::gePose P0, P1, P2, P3;
};

////////////////////////////////////////////////////////////////////////////////
//  Graph Unit tests
///////////////////////////////////////////////////////////////////////////////
//  Number of tests: 6
//
// Test description:
//
//  Test No: 1 - TestCustomNode
//      Description:    Here we will test the node creation ability. Also we will
//                      create similar node to see the output of the unit.
//
//  Test No: 2 - TestCustomNodeFunctions
//      Description:    Here we will test all the functions related to nodes.
//
//  Test No: 3 - TestCustomEdge
//      Description:    Here we will test the edge creation ability. Also we will
//                        create similar edges to see the output of the unit.
//  Test No: 4 - TestCustomEdgeFunctions
//      Description:    Here we will test all the functions related to Edges.
//
//  Test No: 5 - TestCustomGraphUnit
//      Description:    Here we will be testing all the functions related to graphs.

////////////////////////////////////////////////////////////
// Test No: 1 - Nodes
// Tests the node creation ability. Checks for duplicate node.

fmsTest(graphTest, TestNodeCreation)
{
    auto graph = std::make_shared<grGraph>();

    // Testing for multiple node creation.
    EXPECT_NO_THROW(
        graph->addNode("A", P0);
        graph->addNode("B", P1);
        graph->addNode("C", P2);
        graph->addNode("D", P3););

    // Testing for duplicate node creation.
    // This statement should not be able to create a node,
    // It should give a warning to the user without crashing.
    EXPECT_NO_THROW(graph->addNode("D", P3););

    const auto& nodes = graph->nodes();
    // Finding the node and accessing the data stored in it.
    int dIndex = graph->findNode("D");
    // Verify the data in the node to confirm if the node created is
    // working fine.
    EXPECT_NE(dIndex, -1);
    auto dNode = nodes[dIndex];
    EXPECT_EQ(dNode->name(), "D");
    EXPECT_EQ(dNode->pose(), P3);
    EXPECT_EQ(nodes.size(), 4);

    // Remove Node A
    graph->removeNode("A");

    // Finding the node and accessing the data stored in it.
    // Verify the data in the node to confirm if the node created is
    // working fine.
    dIndex = graph->findNode("D");
    EXPECT_NE(dIndex, -1);
    dNode = nodes[dIndex];
    EXPECT_EQ(dNode->name(), "D");
    EXPECT_EQ(dNode->pose(), P3);
    EXPECT_EQ(nodes.size(), 3);
}

////////////////////////////////////////////////////////////
// Test No: 2- Nodes
// Tests the basic functions related to nodes.

fmsTest(graphTest, TestNodeFunctions)
{
    auto graph = std::make_shared<grGraph>();

    // Testing for multiple node initialisation.
    graph->addNode("A", P0);
    graph->addNode("B", P1);
    graph->addNode("C", P2);
    graph->addNode("D", P3);

    // remove an existing node from the graph:
    EXPECT_NO_THROW(graph->removeNode("A"));
    const auto& nodes = graph->nodes();

    // Verify the number of nodes after removal
    EXPECT_EQ(nodes.size(), 3);

    // Removing  a non-existing node from the graph,
    // Should result in NO OP.
    EXPECT_NO_THROW(graph->removeNode("z"));

    // Verify the number of nodes.
    EXPECT_EQ(graph->nodes().size(), 3);
}

////////////////////////////////////////////////////////////////////////////////
// Test No: 3
// Tests the edge creation ability. Duplicate edge creation tested.

fmsTest(graphTest, TestEdgeCreation)
{
    auto graph = std::make_shared<grGraph>();

    // Creating nodes
    graph->addNode("A", P0);
    graph->addNode("B", P1);
    graph->addNode("C", P2);
    graph->addNode("D", P3);

    // TODO(dg) add calls for different types of edge creation.
    // Creating edges with weight.
    EXPECT_NO_THROW(graph->addEdge("A", "B", 10));

    // Creating multiple edges.
    EXPECT_NO_THROW(graph->addEdge("B", "C", 2));

    // Creating edges with already connected node.
    EXPECT_NO_THROW(graph->addEdge("A", "C", 3));

    // Creating edges with the same node.
    EXPECT_NO_THROW(graph->addEdge("A", "A", 2));

    // Checking for the number of edges created.
    EXPECT_EQ(graph->edges().size(), 4);

    // Creating Duplicate edges.
    EXPECT_NO_THROW(graph->addEdge("A", "B", 122));

    // Checking for the number of edges created.
    EXPECT_EQ(graph->edges().size(), 4);
}

// ////////////////////////////////////////////////////////////////////////////////
// // Test No: 4
// // Test the functions related to Edges.

fmsTest(graphTest, TestEdgeFunctions)
{
    auto graph = std::make_shared<grGraph>();

    // Creating nodes
    graph->addNode("A", P0);
    graph->addNode("B", P1);
    graph->addNode("C", P2);
    graph->addNode("D", P3);

    // Creating edges
    graph->addEdge("A", "B", 10);
    graph->addEdge("B", "C", 2);
    graph->addEdge("A", "C", 3);
    graph->addEdge("A", "A", 2);

    // Checking the number of edges in the graph.
    EXPECT_EQ(graph->edges().size(), 4);

    // Checking for creation of edge between two nodes which doesn't exist.
    EXPECT_NO_THROW(graph->addEdge("E", "F", 14));
    fmsRP<grEdge> edgeFound;
    int w = graph->findEdge(edgeFound, "A", "A");
    // Checking for the weight of the edge
    EXPECT_EQ(edgeFound->weight(), 2);

    // Create a self edge. This is not overriding the edge weight, which is not
    graph->addEdge("A", "A", 10);

    EXPECT_EQ(edgeFound->weight(), 2);

    // Checking the number of edges in the graph before the removal of edge.
    EXPECT_EQ(graph->edges().size(), 4);

    // Removal of an edge should not give an error.
    EXPECT_NO_THROW(graph->removeEdge("A", "A"));
    // Checking the no of edges after the removal.
    EXPECT_EQ(graph->edges().size(), 3);

    // Checking the behaviour when the removal operation happens when there is no edge between two nodes.
    EXPECT_NO_THROW(graph->removeEdge("A", "D"));
}

////////////////////////////////////////////////////////////////////////////////
// Test No: 5
// Test the basic functions related to graphs.

fmsTest(graphTest, TestGraphFunctions)
{
    auto graph = std::make_shared<grGraph>();

    // Creating Nodes
    graph->addNode("A", P0);
    graph->addNode("B", P1);
    graph->addNode("C", P2);
    graph->addNode("D", P3);

    // Creating edges
    graph->addEdge("A", "B", 10);
    graph->addEdge("B", "C", 2);
    graph->addEdge("B", "D", 1);
    graph->addEdge("A", "C", 3);
    graph->addEdge("A", "A", 2);

    // Checking the number of edges and nodes currently present in the graph.
    EXPECT_EQ(graph->edges().size(), 5);
    EXPECT_EQ(graph->nodes().size(), 4);

    graph->removeNode("A");
    // Checking the number of edges and nodes after the removal of a node from the graph.
    EXPECT_EQ(graph->nodes().size(), 3);
    EXPECT_EQ(graph->edges().size(), 2);

    EXPECT_NO_THROW(graph->removeEdge("A", "B"));
    EXPECT_EQ(graph->nodes().size(), 3);
    EXPECT_EQ(graph->edges().size(), 2);

    // Removing an existing node
    EXPECT_NO_THROW(graph->removeEdge("B", "D"));
    EXPECT_EQ(graph->edges().size(), 1);
    EXPECT_EQ(graph->nodes().size(), 3);

    // Adding new node after the deletion and verifying that.
    graph->addNode("A", P0);
    EXPECT_EQ(graph->edges().size(), 1);
    EXPECT_EQ(graph->nodes().size(), 4);
}

////////////////////////////////////////////////////////////////////////////////
// Test No: 6
// Read the graph from the file. Move this to map unitTests.

fmsTest(graphTest, TestGraphParser)
{
    grGraphParser graphParser(crFilePath("graph.map"));
    auto graph = graphParser.graph();
}
////////////////////////////////////////////////////////////////////////////////
// Test No: 7
// Read the graph from the file and check if shortest path is working. Move this to map unitTests.

fmsTest(graphTest, TestShortestPath)
{
    grGraphParser graphParser("graph.map");
    auto graph = graphParser.graph();
    auto path = graph.shortestPath("N95", "N56");
    // auto path = graph.shortestPath("N56", "N95");
}

//////////////////////////////////////////////////////////////////////////////////
// TODO(-): Write unitTest to verify
// 0. Verify if both addNodes, removeNodes, all 4 findNodes work.
// 1. Incoming neighbors are all there.
// 2. Neighbors for the node
// 3. Outgoing Neighbors for the node
// 4. Verify the index of the node after addition removal from the field data
// 5. Verify Type of the node, Color, index and other fields. ensure that the graph point is same.
// 6. Verify the in and out degree after addition and removal.
// 7. Edge verify field for different creation methods.
// 9. Verify function calls and indexes.
// 10. Set and check Bi-directionality.
// 11. Shortest path call.
// 12. Nearest Node call.
// 13. Read Graph from file, File needs to placed in test Folder in Assets Folder, path need to be given using fmsPath and verify if the graph is  same and connectivity is same.
// 14. Do a shortest path call on the sample graph.
