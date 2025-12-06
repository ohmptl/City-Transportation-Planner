#pragma once
#include "Graph.h"
#include <vector>
#include <string>

using namespace std;

class NameLookup {
private:
    const Graph& graph;
    vector<string> sortedNames;

public:
    NameLookup(const Graph& g);
    string findClosestMatch(const string& query);
};
