#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "NameLookup.h"

using namespace std;

bool exportPath = false;

void writePathToFile(const vector<string>& pathNames) {
    ofstream outFile("path.txt");
    if (outFile.is_open()) {
        for (size_t i = 0; i < pathNames.size(); ++i) {
            outFile << pathNames[i] << (i < pathNames.size() - 1 ? " " : "");
        }
        outFile << endl;
        outFile.close();
    }
}

// reads the next query from input
bool getNextQuery(string& src, string& dest) {
    string line;
    while (getline(cin, line)) {
        // skip empty lines
        size_t lineStart = line.find_first_not_of(" \t\r\n");
        if (lineStart == string::npos) continue; 
        
        // skip comments
        if (line[lineStart] == '#') continue; 

        // parse the first stop name
        size_t firstWordEnd = line.find_first_of(" \t\r\n", lineStart);
        if (firstWordEnd == string::npos) continue;
        
        src = line.substr(lineStart, firstWordEnd - lineStart);
        
        // parse the second stop name
        size_t secondWordStart = line.find_first_not_of(" \t\r\n", firstWordEnd);
        if (secondWordStart == string::npos) continue;
        
        size_t secondWordEnd = line.find_first_of(" \t\r\n", secondWordStart);
        if (secondWordEnd == string::npos) secondWordEnd = line.length();
        
        dest = line.substr(secondWordStart, secondWordEnd - secondWordStart);
        return true;
    }
    return false;
}

//helper for lookup
bool getNextLookupQuery(string& query) {
    string line;
    while (getline(cin, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) continue;
        if (line[first] == '#') continue;

        size_t end = line.find_first_of(" \t\r\n", first);
        if (end == string::npos) end = line.length();
        
        query = line.substr(first, end - first);
        return true;
    }
    return false;
}

void runDijkstra(const Graph& graph) {
    string src, dest;
    while (getNextQuery(src, dest)) {
        int srcId = graph.getId(src);
        int destId = graph.getId(dest);

        if (srcId == -1 || destId == -1) {
            cout << "error no_path\n";
            continue;
        }

        PathResult result = Dijkstra::findShortestPath(graph, srcId, destId);

        if (result.found) {
            // eta calculation distance / speed (1.4 m/s walking speed)
            double estimatedTime = ceil(result.distance / 1.4);
            cout << "ok " << fixed << setprecision(1) << result.distance << " " << (long long)estimatedTime << "\n";
            
            // output the path for debugging export
            vector<string> pathNames;
            for (size_t i = 0; i < result.path.size(); ++i) {
                string stopName = graph.getName(result.path[i]);
                cerr << stopName;
                if (i < result.path.size() - 1) cerr << " ";
                if (exportPath) pathNames.push_back(stopName);
            }
            cerr << "\n";
            
            if (exportPath) writePathToFile(pathNames);
        } else {
            cout << "error no_path\n";
        }
    }
}

void runAStar(const Graph& graph) {
    string srcName, destName;
    while (getNextQuery(srcName, destName)) {
        int src = graph.getId(srcName);
        int dest = graph.getId(destName);

        if (src == -1 || dest == -1) {
            cout << "error no_path\n";
            continue;
        }

        AStarResult result = AStar::findShortestPath(graph, src, dest);

        if (result.found) {
            double eta = ceil(result.distance / 1.4);
            cout << "ok " << fixed << setprecision(1) << result.distance << " " << (long long)eta << "\n";
            
            //print path to stderr and collect for export
            vector<string> pathNames;
            for (size_t i = 0; i < result.path.size(); ++i) {
                string name = graph.getName(result.path[i]);
                cerr << name;
                if (i < result.path.size() - 1) cerr << " ";
                if (exportPath) pathNames.push_back(name);
            }
            cerr << "\n";
            
            if (exportPath) writePathToFile(pathNames);
        } else {
            cout << "error no_path\n";
        }
    }
}

void runLookup(const Graph& graph) {
    NameLookup lookup(graph);
    string query;
    while (getNextLookupQuery(query)) {
        string match = lookup.findClosestMatch(query);
        if (!match.empty()) {
            cout << "found " << match << "\n";
        } else {
            cout << "not_found\n";
        }
    }
}

int main(int argc, char* argv[]) {
    string mode = "dijkstra";
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--astar") mode = "astar";
        else if (arg == "--lookup") mode = "lookup";
        else if (arg == "--export") exportPath = true;
    }

    Graph graph;
    graph.loadFromFile("data/edges.txt");

    // make input output faster
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (mode == "dijkstra") {
        runDijkstra(graph);
    } else if (mode == "astar") {
        runAStar(graph);
    } else if (mode == "lookup") {
        runLookup(graph);
    }

    return 0;
}
