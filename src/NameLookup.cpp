#include "NameLookup.h"
#include <algorithm>
#include <iostream>

NameLookup::NameLookup(const Graph& g) : graph(g) {
    sortedNames = graph.getAllNames();
    sort(sortedNames.begin(), sortedNames.end());
}

string NameLookup::findClosestMatch(const string& query) {
    if (query.empty()) return "";
    auto it = lower_bound(sortedNames.begin(), sortedNames.end(), query);
    
    if (it != sortedNames.end()) {
        // check if it starts with query
        if (it->rfind(query, 0) == 0) {
            return *it;
        }
    }
    
    return "";
}