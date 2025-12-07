#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Edge {
    int to;
    double weight;
};

class Graph {
private:
    int numVertices;
    unordered_map<string, int> nameToId;
    vector<string> idToName;
    // CSR representation
    vector<Edge> allEdges;
    vector<int> edgeHead; // index into allEdges

    // for a* synthetic coordinates
    vector<pair<double, double>> coordinates;

    void generateCoordinates(int v, const string& name);

public:
    Graph();
    void loadFromFile(const string& filename);
    int getNumVertices() const;
    int getId(const string& name) const; // returns -1 if not found
    string getName(int id) const;
    
    // Returns a pair of iterators (begin, end)
    pair<vector<Edge>::const_iterator, vector<Edge>::const_iterator> getNeighborsIter(int stopId) const;
    
    // Keep old API for compatibility if needed, but we will change implementation
    // const vector<Edge>& getNeighbors(int stopId) const; // REMOVED to force update
    
    // for a*
    double getEuclideanDistance(int stopId1, int stopId2) const;
    
    bool isValidVertex(int stopId) const;
    
    // for namelookup
    const vector<string>& getAllNames() const;
};
