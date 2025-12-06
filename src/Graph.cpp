#include "Graph.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>
#include <iostream>

Graph::Graph() : numVertices(0) {}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string stopOne, stopTwo, len_str;
        if (!(ss >> stopOne >> stopTwo >> len_str)) continue;

        double weight;
        try {
            size_t idx;
            weight = stod(len_str, &idx);
            //ensure the whole string was parsed as a number to avoid partial matches 
            //on headers like "length_m"
            if (idx != len_str.length()) {
                 //check if the rest is just whitespace
                 bool trailing_garbage = false;
                 for(size_t k=idx; k<len_str.length(); ++k) {
                     if(!isspace(len_str[k])) trailing_garbage = true;
                 }
                 if(trailing_garbage) throw invalid_argument("Not a number");
            }
        } catch (...) {
            //likely a header line
            continue;
        }

        int stopOneId = getId(stopOne);
        if (stopOneId == -1) {
            stopOneId = numVertices++;
            nameToId[stopOne] = stopOneId;
            idToName.push_back(stopOne);
            adj.resize(numVertices);
            coordinates.resize(numVertices);
            generateCoordinates(stopOneId, stopOne);
        }

        int stopTwoId = getId(stopTwo);
        if (stopTwoId == -1) {
            stopTwoId = numVertices++;
            nameToId[stopTwo] = stopTwoId;
            idToName.push_back(stopTwo);
            adj.resize(numVertices);
            coordinates.resize(numVertices);
            generateCoordinates(stopTwoId, stopTwo);
        }

        adj[stopOneId].push_back({stopTwoId, weight});
        adj[stopTwoId].push_back({stopOneId, weight});
    }
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

const vector<Edge>& Graph::getNeighbors(int stopId) const {
    return adj[stopId];
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
