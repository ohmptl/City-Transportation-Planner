#include "NameLookup.h"
#include <algorithm>
#include <iostream>

NameLookup::NameLookup(const Graph& g) : graph(g) {
    sortedNames = graph.getAllNames();
    std::sort(sortedNames.begin(), sortedNames.end());
}

std::string NameLookup::findClosestMatch(const std::string& query) {
    if (query.empty()) return "";
    auto it = std::lower_bound(sortedNames.begin(), sortedNames.end(), query);
    
    if (it != sortedNames.end()) {
        // Check if it starts with query
        if (it->rfind(query, 0) == 0) {
            return *it;
        }
    }
    
    return "";
}
