#include <stdio.h>
#include <stdlib.h>
#include "minHeap.h"

HeapNode *create_node(int v, int d)
{
    HeapNode* new = (HeapNode*) malloc(sizeof(HeapNode));
    new->vertex = v;
    new->dist = d;
    new->left = NULL;
    new->right = NULL;
    return new;
}

MinHeap *create_heap(int capacity)
{
    MinHeap *new = (MinHeap*) malloc(sizeof(MinHeap));
    new->capacity = capacity;
    new->size=0;
    new->pos = (int *) malloc(capacity * sizeof(int));
    new->array = (HeapNode**) malloc(capacity * sizeof(HeapNode*));
    return new;
}

void swapNodes(HeapNode** a, HeapNode** b)
{
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void Heapify(MinHeap* heap, int id)
{
    int smallest, left, right;
    smallest = id;
    left = 2*id + 1;
    right = 2*id + 2;
    
    //if element exists and its distance is smaller than the current smallest, we will swap them
    if(left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist)
        smallest = left;
    if(right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist)
        smallest = right;

    if(smallest != id)
    {
        //get the two nodes
        HeapNode* smallestNode = heap->array[smallest];
        HeapNode* idNode = heap->array[id];
        
        //swap their positions
        heap->pos[smallestNode->vertex] = id;
        heap->pos[idNode->vertex] = smallest;

        //swap their nodes
        swapNodes(&heap->array[smallest],&heap->array[id]);

        //continue heapifying until done!
        Heapify(heap,smallest);
        
    }
}

HeapNode *removeSmallest(MinHeap *heap)
{
    if(heap->size == 0)
        return NULL;

    //store the smallest
    HeapNode *smallest = heap->array[0];
    //store the last node and then set it to the first one
    HeapNode *last = heap->array[heap->size-1];
    heap->array[0] = last;

    //update pos of last node
    heap->pos[smallest->vertex] = heap->size-1;
    heap->pos[last->vertex] = 0;
    //reduce its size
    --heap->size;
    //~heapify~
    Heapify(heap,0);

    return smallest;
}

// can adjust the distance of a vertex within our heap
void adjustDistInHeap(MinHeap *heap, int vertex, int distance)
{
    int i = heap->pos[vertex];
    heap->array[i]->dist = distance;

    //swap with parent if smol
    while(i > 0 && heap->array[i]->dist < heap->array[(i-1)/2]->dist)
    {
        //swap pos w parent
        heap->pos[heap->array[i]->vertex] = (i-1)/2;
        heap->pos[heap->array[(i-1)/2]->vertex] = i;

        //swap node w parent
        swapNodes(&heap->array[i],&heap->array[(i-1)/2]);

        //goto new parent
        i = (i-1)/2;
    }
}

void heapInsert(MinHeap *heap, HeapNode *node)
{
    //Increase heap size by 1
    ++heap->size;
    //Start at the end of the heap
    int i = heap->size - 1;

    //Put the new node in the proper place
    while(i && node->dist < heap->array[(i-1)/2]->dist)
    {
        heap->array[i] = heap->array[(i-1)/2];
        i = (i-1)/2;
    }

    heap->array[i] = node;
}

void HeapifyEntire(MinHeap* heap)
{
    int n = heap->size - 1;
    for(int i = (n-1)/2;i>=0;--i)
        Heapify(heap,i);
}

int isLeaf(HeapNode *node)
{
    return !(node->left) && !(node->right);
}

void prepareHeap(MinHeap *heap, int *frequency, int size)
{
    for(int i=0;i<size;++i)
    {
        heap->array[i] = create_node(i,frequency[i]);
        ++heap->size;
    }
    HeapifyEntire(heap);
}

HeapNode *buildHuffmanTree(MinHeap *heap)
{
    HeapNode *left, *right, *parent;

    while(heap->size > 1)
    {
        left = removeSmallest(heap);
        right = removeSmallest(heap);
        parent = create_node(-1,left->dist + right->dist);
        parent->left = left; parent->right = right;
        heapInsert(heap,parent);
    }

    return removeSmallest(heap);
}