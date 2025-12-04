#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <sstream>
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "NameLookup.h"

// Helper to read next valid line, skipping comments and empty lines
bool getNextQuery(std::string& srcName, std::string& destName) {
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) continue; // Empty/whitespace
        if (line[first] == '#') continue; // Comment

        std::stringstream ss(line);
        if (ss >> srcName >> destName) return true;
    }
    return false;
}

// Helper for lookup
bool getNextLookupQuery(std::string& query) {
    std::string line;
    while (std::getline(std::cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) continue;
        if (line[first] == '#') continue;

        std::stringstream ss(line);
        if (ss >> query) return true;
    }
    return false;
}

void runDijkstra(const Graph& graph) {
    std::string srcName, destName;
    while (getNextQuery(srcName, destName)) {
        int src = graph.getId(srcName);
        int dest = graph.getId(destName);

        if (src == -1 || dest == -1) {
            std::cout << "error no_path" << std::endl;
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();
        PathResult result = Dijkstra::findShortestPath(graph, src, dest);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (result.found) {
            double eta = std::ceil(result.distance / 1.4);
            std::cout << "ok " << std::fixed << std::setprecision(1) << result.distance << " " << (long long)eta << std::endl;
            
            // Print path to stderr
            for (size_t i = 0; i < result.path.size(); ++i) {
                std::cerr << graph.getName(result.path[i]);
                if (i < result.path.size() - 1) std::cerr << " ";
            }
            std::cerr << std::endl;
            std::cerr << "debug: expanded=" << result.expandedNodes << " time=" << elapsed.count() << "s" << std::endl;
        } else {
            std::cout << "error no_path" << std::endl;
        }
    }
}

void runAStar(const Graph& graph) {
    std::string srcName, destName;
    while (getNextQuery(srcName, destName)) {
        int src = graph.getId(srcName);
        int dest = graph.getId(destName);

        if (src == -1 || dest == -1) {
            std::cout << "error no_path" << std::endl;
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();
        AStarResult result = AStar::findShortestPath(graph, src, dest);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (result.found) {
            double eta = std::ceil(result.distance / 1.4);
            std::cout << "ok " << std::fixed << std::setprecision(1) << result.distance << " " << (long long)eta << std::endl;
            
            // Print path to stderr
            for (size_t i = 0; i < result.path.size(); ++i) {
                std::cerr << graph.getName(result.path[i]);
                if (i < result.path.size() - 1) std::cerr << " ";
            }
            std::cerr << std::endl;
            
            std::cerr << "debug: expanded=" << result.expandedNodes << " time=" << elapsed.count() << "s" << std::endl;
        } else {
            std::cout << "error no_path" << std::endl;
        }
    }
}

void runLookup(const Graph& graph) {
    NameLookup lookup(graph);
    std::string query;
    while (getNextLookupQuery(query)) {
        std::string match = lookup.findClosestMatch(query);
        if (!match.empty()) {
            std::cout << "found " << match << std::endl;
        } else {
            std::cout << "not_found" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    std::string mode = "dijkstra";
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--astar") mode = "astar";
        else if (arg == "--lookup") mode = "lookup";
    }

    Graph graph;
    graph.loadFromFile("data/edges.txt");

    if (mode == "dijkstra") {
        runDijkstra(graph);
    } else if (mode == "astar") {
        runAStar(graph);
    } else if (mode == "lookup") {
        runLookup(graph);
    }

    return 0;
}
