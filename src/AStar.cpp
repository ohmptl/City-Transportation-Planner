#include "AStar.h"
#include "MinHeap.h"
#include <limits>
#include <algorithm>

AStarResult AStar::findShortestPath(const Graph& graph, int src, int dest) {
    int n = graph.getNumVertices();
    vector<double> g_score(n, numeric_limits<double>::infinity());
    vector<int> parent(n, -1);
    int expanded = 0;
    
    MinHeap pq(n);
    
    g_score[src] = 0;
    double f_start = graph.getEuclideanDistance(src, dest);
    pq.insert(src, f_start);
    
    while (!pq.isEmpty()) {
        HeapNode minNode = pq.extractMin();
        int u = minNode.vertex;
        
        // if we popped it then we are expanding it
        expanded++;
        
        if (u == dest) break;

        for (const auto& edge : graph.getNeighbors(u)) {
            int v = edge.to;
            double weight = edge.weight;
            
            double tentative_g = g_score[u] + weight;
            
            if (tentative_g < g_score[v]) {
                g_score[v] = tentative_g;
                parent[v] = u;
                double f_v = tentative_g + graph.getEuclideanDistance(v, dest);
                
                if (pq.isInMinHeap(v)) {
                    pq.decreaseKey(v, f_v);
                } else {
                    //reinsert if not in heap
                    //either new or closed
                    pq.insert(v, f_v);
                }
            }
        }
    }
    
    AStarResult result;
    result.expandedNodes = expanded;
    
    if (g_score[dest] == numeric_limits<double>::infinity()) {
        result.found = false;
        result.distance = -1;
    } else {
        result.found = true;
        result.distance = g_score[dest];
        
        int curr = dest;
        while (curr != -1) {
            result.path.push_back(curr);
            curr = parent[curr];
        }
        reverse(result.path.begin(), result.path.end());
    }
    
    return result;
}
