#pragma once
#include "Graph.h"
#include <vector>
#include <string>

class NameLookup {
private:
    const Graph& graph;
    std::vector<std::string> sortedNames;

public:
    NameLookup(const Graph& g);
    std::string findClosestMatch(const std::string& query);
};
