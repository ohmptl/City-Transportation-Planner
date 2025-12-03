#include "runtime_meter.hpp"

int main() {
  rt::ScopeTimer timer("runtime_ms"); // prints to STDERR on exit

  // ... load graph from ./data/edges.txt ...
  // ... read queries from STDIN and answer ...

  return 0;
}