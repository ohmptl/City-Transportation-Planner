#include "MinHeap.h"
#include <algorithm>
#include <iostream>

MinHeap::MinHeap(int cap) : size(0), capacity(cap) {
    heap.resize(capacity);
    pos.assign(capacity, -1);
}

void MinHeap::swapNodes(int i, int j) {
    HeapNode temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;

    pos[heap[i].vertex] = i;
    pos[heap[j].vertex] = j;
}

void MinHeap::heapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left].dist < heap[smallest].dist)
        smallest = left;

    if (right < size && heap[right].dist < heap[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swapNodes(idx, smallest);
        heapify(smallest);
    }
}

void MinHeap::insert(int vertex, double dist) {
    if (size == capacity) {
        // Handle resize if necessary, but spec says ~10k vertices, so we can preallocate or just resize
        // For now, let's assume capacity is sufficient or resize
        capacity *= 2;
        heap.resize(capacity);
        pos.resize(capacity, -1);
    }

    size++;
    int i = size - 1;
    heap[i] = {vertex, dist};
    pos[vertex] = i;

    while (i != 0 && heap[(i - 1) / 2].dist > heap[i].dist) {
        swapNodes(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

HeapNode MinHeap::extractMin() {
    if (isEmpty()) {
        return {-1, -1.0};
    }

    HeapNode root = heap[0];
    HeapNode lastNode = heap[size - 1];
    heap[0] = lastNode;

    pos[root.vertex] = -1; // Removed
    pos[lastNode.vertex] = 0;

    size--;
    heapify(0);

    return root;
}

void MinHeap::decreaseKey(int vertex, double newDist) {
    int i = pos[vertex];
    if (i == -1) return; // Not in heap

    heap[i].dist = newDist;

    while (i != 0 && heap[(i - 1) / 2].dist > heap[i].dist) {
        swapNodes(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

bool MinHeap::isEmpty() const {
    return size == 0;
}

bool MinHeap::isInMinHeap(int vertex) const {
    if (vertex < 0 || vertex >= (int)pos.size()) return false;
    return pos[vertex] != -1;
}
