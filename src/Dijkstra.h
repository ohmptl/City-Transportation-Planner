#pragma once
#include "Graph.h"
#include <vector>

using namespace std;

struct PathResult {
    double distance;
    vector<int> path; // sequence of vertex ids
    bool found;
    int expandedNodes;
};

class Dijkstra {
public:
    static PathResult findShortestPath(const Graph& graph, int src, int dest, bool storePath = true);
};
