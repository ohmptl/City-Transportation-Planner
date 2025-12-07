#include "Graph.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

Graph::Graph() : numVertices(0) {}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Temporary adjacency list
    vector<vector<Edge>> tempAdj;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Manual parsing is faster than stringstream
        size_t start = line.find_first_not_of(" \t");
        if (start == string::npos) continue;
        
        size_t first_space = line.find_first_of(" \t", start);
        if (first_space == string::npos) continue;
        
        string stopOne = line.substr(start, first_space - start);
        
        size_t second_word_start = line.find_first_not_of(" \t", first_space);
        if (second_word_start == string::npos) continue;
        
        size_t second_space = line.find_first_of(" \t", second_word_start);
        if (second_space == string::npos) continue;
        
        string stopTwo = line.substr(second_word_start, second_space - second_word_start);
        
        size_t weight_start = line.find_first_not_of(" \t", second_space);
        if (weight_start == string::npos) continue;
        
        string len_str = line.substr(weight_start);

        double weight;
        try {
            size_t idx;
            weight = stod(len_str, &idx);
        } catch (...) {
            //likely a header line
            continue;
        }

        int stopOneId;
        auto it1 = nameToId.find(stopOne);
        if (it1 == nameToId.end()) {
            stopOneId = numVertices++;
            nameToId.emplace(stopOne, stopOneId);
            idToName.push_back(stopOne);
            tempAdj.resize(numVertices);
            coordinates.resize(numVertices);
            generateCoordinates(stopOneId, stopOne);
        } else {
            stopOneId = it1->second;
        }

        int stopTwoId;
        auto it2 = nameToId.find(stopTwo);
        if (it2 == nameToId.end()) {
            stopTwoId = numVertices++;
            nameToId.emplace(stopTwo, stopTwoId);
            idToName.push_back(stopTwo);
            tempAdj.resize(numVertices);
            coordinates.resize(numVertices);
            generateCoordinates(stopTwoId, stopTwo);
        } else {
            stopTwoId = it2->second;
        }

        tempAdj[stopOneId].push_back({stopTwoId, weight});
        tempAdj[stopTwoId].push_back({stopOneId, weight});
    }

    // Convert to CSR
    edgeHead.resize(numVertices + 1);
    size_t totalEdges = 0;
    for (const auto& neighbors : tempAdj) {
        totalEdges += neighbors.size();
    }
    allEdges.reserve(totalEdges);

    for (int i = 0; i < numVertices; ++i) {
        edgeHead[i] = allEdges.size();
        allEdges.insert(allEdges.end(), tempAdj[i].begin(), tempAdj[i].end());
    }
    edgeHead[numVertices] = allEdges.size();
}

int Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getId(const string& name) const {
    auto it = nameToId.find(name);
    if (it != nameToId.end()) {
        return it->second;
    }
    return -1;
}

string Graph::getName(int id) const {
    if (id >= 0 && id < numVertices) {
        return idToName[id];
    }
    return "";
}

pair<vector<Edge>::const_iterator, vector<Edge>::const_iterator> Graph::getNeighborsIter(int stopId) const {
    if (stopId < 0 || stopId >= numVertices) {
        return {allEdges.end(), allEdges.end()};
    }
    return {allEdges.begin() + edgeHead[stopId], allEdges.begin() + edgeHead[stopId + 1]};
}

void Graph::generateCoordinates(int stopId, const string& name) {
    hash<string> hasher;
    size_t h = hasher(name);
    // get x and y
    double x = (h % 10000);
    
    size_t h2 = hasher(name + "_salt_for_y");
    double y = (h2 % 10000);
    
    coordinates[stopId] = {x, y};
}

double Graph::getEuclideanDistance(int stopId1, int stopId2) const {
    if (stopId1 < 0 || stopId1 >= numVertices || stopId2 < 0 || stopId2 >= numVertices) return 0.0;
    double dx = coordinates[stopId1].first - coordinates[stopId2].first;
    double dy = coordinates[stopId1].second - coordinates[stopId2].second;
    return sqrt(dx*dx + dy*dy);
}

bool Graph::isValidVertex(int stopId) const {
    return stopId >= 0 && stopId < numVertices;
}

const vector<string>& Graph::getAllNames() const {
    return idToName;
}
