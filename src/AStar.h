#pragma once
#include "Graph.h"
#include <vector>

struct AStarResult {
    double distance;
    std::vector<int> path;
    bool found;
    int expandedNodes;
};

class AStar {
public:
    static AStarResult findShortestPath(const Graph& graph, int src, int dest);
};
