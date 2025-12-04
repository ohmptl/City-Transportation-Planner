#include "Dijkstra.h"
#include "MinHeap.h"
#include <limits>
#include <algorithm>

PathResult Dijkstra::findShortestPath(const Graph& graph, int src, int dest) {
    int n = graph.getNumVertices();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    
    MinHeap pq(n);
    
    int expanded = 0;
    
    dist[src] = 0;
    pq.insert(src, 0);
    
    while (!pq.isEmpty()) {
        HeapNode minNode = pq.extractMin();
        int u = minNode.vertex;
        double d = minNode.dist;
        
        expanded++;
        
        if (d > dist[u]) continue;
        if (u == dest) break; 
        
        for (const auto& edge : graph.getNeighbors(u)) {
            int v = edge.to;
            double weight = edge.weight;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                
                if (pq.isInMinHeap(v)) {
                    pq.decreaseKey(v, dist[v]);
                } else {
                    pq.insert(v, dist[v]);
                }
            }
        }
    }
    
    PathResult result;
    result.expandedNodes = expanded;
    if (dist[dest] == std::numeric_limits<double>::infinity()) {
        result.found = false;
        result.distance = -1;
    } else {
        result.found = true;
        result.distance = dist[dest];
        
        int curr = dest;
        while (curr != -1) {
            result.path.push_back(curr);
            curr = parent[curr];
        }
        std::reverse(result.path.begin(), result.path.end());
    }
    
    return result;
}
