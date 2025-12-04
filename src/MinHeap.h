#pragma once
#include <vector>
#include <unordered_map>
#include <limits>

struct HeapNode {
    int vertex;
    double dist;
};

class MinHeap {
private:
    std::vector<HeapNode> heap;
    std::vector<int> pos; // Maps vertex ID to heap index. -1 if not in heap.
    int size;
    int capacity;

    void swapNodes(int i, int j);
    void heapify(int idx);

public:
    MinHeap(int capacity);
    void insert(int vertex, double dist);
    HeapNode extractMin();
    void decreaseKey(int vertex, double newDist);
    bool isEmpty() const;
    bool isInMinHeap(int vertex) const;
};
