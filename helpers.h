#ifndef _HELPERS_H
#define _HELPERS_H_
#include "minHeap.h"
void create_frequency_array(char *filename, int* frequency);
void encode_file(char *filename, char**dictionary);
void decode_file(char *filename, char**dictionary);

void dump(HeapNode *node, int encoding[], int height);

void dump_to_array(HeapNode *node, char encoding[], int height, char **dictionary);

#endif