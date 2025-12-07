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
    HeapNode node = heap[idx];
    double val = node.dist;

    while (true) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].dist < val)
            smallest = left;

        if (right < size && heap[right].dist < (smallest == idx ? val : heap[smallest].dist))
            smallest = right;

        if (smallest != idx) {
            heap[idx] = heap[smallest];
            pos[heap[idx].vertex] = idx;
            idx = smallest;
        } else {
            break;
        }
    }
    heap[idx] = node;
    pos[node.vertex] = idx;
}

void MinHeap::insert(int vertex, double dist) {
    if (size == capacity) {
        //if the heap is full then double its size
        capacity *= 2;
        heap.resize(capacity);
        pos.resize(capacity, -1);
    }

    size++;
    int i = size - 1;
    
    // Bubble up with hole
    while (i != 0) {
        int parentIdx = (i - 1) / 2;
        if (heap[parentIdx].dist <= dist) break;
        
        heap[i] = heap[parentIdx];
        pos[heap[i].vertex] = i;
        i = parentIdx;
    }

    heap[i] = {vertex, dist};
    pos[vertex] = i;
}

HeapNode MinHeap::extractMin() {
    if (isEmpty()) {
        return {-1, -1.0};
    }

    HeapNode root = heap[0];
    HeapNode lastNode = heap[size - 1];
    
    pos[root.vertex] = -1; // removed
    size--;

    if (size > 0) {
        // Instead of full swap and heapify, we can just place lastNode at root and sift down
        // But heapify(0) does exactly that if we put it there.
        // With hole optimization in heapify, we put lastNode in 'node' variable implicitly?
        // No, heapify takes idx. It assumes heap[idx] is the one to sift.
        // So we must put lastNode at 0.
        heap[0] = lastNode;
        pos[lastNode.vertex] = 0;
        heapify(0);
    }

    return root;
}

void MinHeap::decreaseKey(int vertex, double newDist) {
    int i = pos[vertex];
    if (i == -1) return; // not in heap

    heap[i].dist = newDist;
    
    HeapNode node = heap[i];
    while (i != 0) {
        int parentIdx = (i - 1) / 2;
        if (heap[parentIdx].dist <= node.dist) break;
        
        heap[i] = heap[parentIdx];
        pos[heap[i].vertex] = i;
        i = parentIdx;
    }
    heap[i] = node;
    pos[node.vertex] = i;
}

bool MinHeap::isEmpty() const {
    return size == 0;
}

bool MinHeap::isInMinHeap(int vertex) const {
    if (vertex < 0 || vertex >= (int)pos.size()) return false;
    return pos[vertex] != -1;
}

void MinHeap::reset() {
    for (int i = 0; i < size; ++i) {
        pos[heap[i].vertex] = -1;
    }
    size = 0;
}
