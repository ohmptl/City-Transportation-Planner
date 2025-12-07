#pragma once
#include "Graph.h"
#include <vector>

using namespace std;

struct AStarResult {
    double distance;
    vector<int> path;
    bool found;
    int expandedNodes;
};

class AStar {
public:
    static AStarResult findShortestPath(const Graph& graph, int src, int dest, bool storePath = true);
};
