#include "Dijkstra.h"
#include "MinHeap.h"
#include <limits>
#include <algorithm>

PathResult Dijkstra::findShortestPath(const Graph& graph, int src, int dest) {
    int n = graph.getNumVertices();
    
    //use static variables to avoid allocating memory over and over again
    static vector<double> minDistance;
    static vector<int> parent;
    static vector<int> touched;
    static MinHeap priorityQueue(0);
    static bool initialized = false;
    static int current_n = 0;

    if (!initialized || current_n < n) {
        minDistance.assign(n, numeric_limits<double>::infinity());
        parent.assign(n, -1);
        touched.reserve(n);
        
        priorityQueue = MinHeap(n); 
        current_n = n;
        initialized = true;
    }

    //only reset the nodes we touched in the last run
    for (int v : touched) {
        minDistance[v] = numeric_limits<double>::infinity();
        parent[v] = -1;
    }
    touched.clear();
    
    priorityQueue.reset();
    
    int expanded = 0;
    
    minDistance[src] = 0;
    touched.push_back(src);
    priorityQueue.insert(src, 0);
    
    while (!priorityQueue.isEmpty()) {
        HeapNode minNode = priorityQueue.extractMin();
        int u = minNode.vertex;
        double d = minNode.dist;
        
        expanded++;
        
        //if we found a shorter path already then skip
        if (d > minDistance[u]) continue;
        
        //if we reached the destination then we can stop
        if (u == dest) break; 
        
        for (const auto& edge : graph.getNeighbors(u)) {
            int v = edge.to;
            double weight = edge.weight;
            
            if (minDistance[u] + weight < minDistance[v]) {
                //if this is the first time we touch this node then mark it for reset later
                if (minDistance[v] == numeric_limits<double>::infinity()) {
                    touched.push_back(v);
                }
                
                minDistance[v] = minDistance[u] + weight;
                parent[v] = u;
                
                if (priorityQueue.isInMinHeap(v)) {
                    priorityQueue.decreaseKey(v, minDistance[v]);
                } else {
                    priorityQueue.insert(v, minDistance[v]);
                }
            }
        }
    }
    
    PathResult result;
    result.expandedNodes = expanded;
    
    if (minDistance[dest] == std::numeric_limits<double>::infinity()) {
        result.found = false;
        result.distance = -1;
    } else {
        result.found = true;
        result.distance = minDistance[dest];
        
        // reconstruct the path by backtracking
        int curr = dest;
        while (curr != -1) {
            result.path.push_back(curr);
            curr = parent[curr];
        }
        std::reverse(result.path.begin(), result.path.end());
    }
    
    return result;
}
