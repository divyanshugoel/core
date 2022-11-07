// Copyright 2022 Divyanshu Goel.
#pragma once

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "core/core/Core.h"
#include "core/file/FileUtils.h"
#include "json/json.h"

#include "graph/graph/Graph.h"

////////////////////////////////////////////////////////////////////////////////
// Reads a basic directed graph from an input file.
// The allowed fields for Node:
//
// The allowed fields for Edge:
//
// The information is to be saved in binary format in future. The details for graph
// are serialized and then stored, the entire map is read instead of graph, as there
// would not be a concept of graph explicitly.

class grGraphParser
{
public:
    // Constructor initialization with the file path.
    grGraphParser(const crFilePath& fileName = "graph.map")
        : mFileName(fileName)
    {
        read();
    };
    // Close the file handle for json readers
    ~grGraphParser()
    {
        close();
    };
    // Returns the graph
    void read();
    // Returns the graph
    void close();
    // Returns the graph
    grGraph graph() const
    {
        return mGraphData;
    };

private:
    // Read all the nodes.
    void readNodes();
    // Read a single node.
    grNode readNode(int index);
    // Read all the connections.
    void readConnections();
    // Read a single connection.
    grEdge readConnection(int index);

private:
    // Stores the file Path
    crFilePath mFileName;
    // Stores the input file stream
    std::ifstream mIfs;
    // Instances to JSON reader
    Json::Reader mReader;
    Json::Value mObj;
    // Stores the graph;
    grGraph mGraphData;
};
