#ifndef _MINHEAP_H_
#define _MINHEAP_H_
#include <stdio.h>
#include <stdlib.h>

/* Reusing HW 6 Min Heap Functionality - 
 * Vertex = ASCII CHAR INT REPRESENTATION
 * DIST = # APPEARANCES IN THE TEXT
*/
typedef struct HeapNode{
    int vertex;
    int dist;
    struct HeapNode *left,*right;
} HeapNode;

typedef struct MinHeap{
    int size;
    int capacity;
    int *pos;
    HeapNode **array;
} MinHeap;

HeapNode *create_node(int v, int d);

MinHeap *create_heap(int capacity);

void swapNodes(HeapNode** a, HeapNode** b);

void Heapify(MinHeap* heap, int id);

HeapNode *removeSmallest(MinHeap *heap);

void adjustDistInHeap(MinHeap *heap, int vertex, int distance);

void heapInsert(MinHeap *heap, HeapNode *node);

void HeapifyEntire(MinHeap* heap);

int isLeaf(HeapNode *node);

void prepareHeap(MinHeap *heap, int *frequency, int size);

HeapNode *buildHuffmanTree(MinHeap *heap);

#endif