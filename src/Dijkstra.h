#pragma once
#include "Graph.h"
#include <vector>

struct PathResult {
    double distance;
    std::vector<int> path; // Sequence of vertex IDs
    bool found;
    int expandedNodes;
};

class Dijkstra {
public:
    static PathResult findShortestPath(const Graph& graph, int src, int dest);
};
