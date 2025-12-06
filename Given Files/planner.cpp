#include "runtime_meter.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Include your existing headers
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"

// Optional: path export
void writePath(const std::vector<std::string>& path) {
    if (path.empty()) return;
    std::ofstream fout("path.txt");
    for (const auto& stop : path) fout << stop << "\n";
    fout.close();
}

int main() {
    rt::ScopeTimer timer("runtime_ms"); // automatically prints runtime

    // Load the graph
    Graph graph;
    graph.loadFromFile("./data/edges.txt"); // assumes you have this function

    std::cout << "Graph loaded with " << graph.size() << " stops.\n";

    // Read queries from STDIN
    std::string src, dst;
    std::cout << "Enter queries (source destination), Ctrl+D to finish:\n";
    while (std::cin >> src >> dst) {
        std::vector<std::string> path;
        double distance = 0.0;

        // Choose algorithm here, e.g., Dijkstra
        distance = dijkstra(graph, src, dst, path);

        if (path.empty()) {
            std::cout << "No path found from " << src << " to " << dst << "\n";
        } else {
            std::cout << "Distance: " << distance << "\nPath: ";
            for (const auto& stop : path) std::cout << stop << " ";
            std::cout << "\n";

            // Optional: export path
            writePath(path);
        }
    }

    return 0;
}
