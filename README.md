# City Transportation Planner

A high-performance C++ pathfinding engine for city transportation networks. This project implements optimized Dijkstra and A* algorithms to find the shortest paths between transit stops.

## Features

*   **Fast Pathfinding**: Optimized implementation of Dijkstra's algorithm and A* search.
*   **Smart Name Lookup**: Fuzzy search capability to find station names.
*   **Performance**: Uses custom MinHeap and static memory allocation for minimal overhead.
*   **Flexible Input**: Reads graph data from edge lists and processes queries from standard input.

## Building the Project

Requirements:
*   C++17 compatible compiler (g++)
*   Make

To build the project, simply run:

```bash
make
```

This will create the `planner` executable.

## Usage

The program reads the graph structure from `data/edges.txt` by default.

### 1. Standard Pathfinding (Dijkstra)

Run the planner and provide queries via standard input (or pipe a file):

```bash
./planner
```

**Input Format:**
Each line should contain two station names separated by whitespace.
```text
"Station A" "Station B"
```

**Output:**
```text
ok <distance> <eta>
```

### 2. A* Search

To use the A* algorithm (which uses Euclidean distance heuristics):

```bash
./planner --astar
```

### 3. Station Name Lookup

To search for a station name:

```bash
./planner --lookup
```

Type a partial name, and the tool will return the closest match.

### 4. Export Path

To export the sequence of stops for the found path to `path.txt`:

```bash
./planner --export
```

## Project Structure

*   `src/main.cpp`: Entry point and query handling.
*   `src/Graph.cpp`: Graph data structure and file loading.
*   `src/Dijkstra.cpp`: Optimized Dijkstra implementation.
*   `src/AStar.cpp`: A* search implementation.
*   `src/MinHeap.cpp`: Custom binary heap for priority queue operations.
*   `src/NameLookup.cpp`: Utility for finding station names.

## Performance Notes

The pathfinding core is optimized for high-throughput queries using:
*   Static memory reuse to reduce allocation overhead.
*   Sparse reset logic to avoid $O(V)$ initialization for every query.
*   Fast I/O synchronization.

---
*Created for ECE 309 Final Project.*