#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

struct Edge {
    int to;
    double weight;
};

class Graph {
private:
    int numVertices;
    std::unordered_map<std::string, int> nameToId;
    std::vector<std::string> idToName;
    std::vector<std::vector<Edge>> adj;
    
    // For A* synthetic coordinates
    std::vector<std::pair<double, double>> coordinates;

    void generateCoordinates(int v, const std::string& name);

public:
    Graph();
    void loadFromFile(const std::string& filename);
    int getNumVertices() const;
    int getId(const std::string& name) const; // Returns -1 if not found
    std::string getName(int id) const;
    const std::vector<Edge>& getNeighbors(int u) const;
    
    // For A*
    double getEuclideanDistance(int u, int v) const;
    
    bool isValidVertex(int v) const;
    
    // For NameLookup
    const std::vector<std::string>& getAllNames() const;
};
