#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minHeap.h"

/* Create the frequency table from an input file
 * Arguments:
    * filename
    * frequency_list: this is an array of size 128, where each array element contains the number of times each char occurs (i.e. frequency_list[65] = the number of times 'A' occurs)
    * ^^ NEED TO SET THESE ALL TO 0 TO START
*/
void create_frequency_array(char *filename, int* frequency)
{
    FILE *fp;
    int c;

    fp = fopen(filename,"r");
    while (!feof(fp))
    {
        c = fgetc(fp);
        ++frequency[c];
    }
    fclose(fp);
}

void encode_file(char *filename, char**dictionary)
{
    FILE *fp;
    int c,bit_counter;
    bit_counter = 0;

    fp = fopen(filename,"r");
    while(!feof(fp))
    {
        c = fgetc(fp);
        if(feof(fp))
            break;
        //translate the char and print it
        printf("%s",dictionary[(int)c]);
        bit_counter += strlen(dictionary[(int)c]);
    }
    fclose(fp);
    printf("\n\n\n %d bits to encode this document.\n\n",bit_counter);
}

void decode_file(char *filename, char**dictionary)
{
    FILE *fp;
    char ch;
    int counter=0;
    char *try_this_token = malloc(sizeof(char)*50);
    memset(try_this_token,'\0',50);

    fp = fopen(filename,"r");
    while(!feof(fp))
    {
        ch = fgetc(fp);
        memcpy(try_this_token+counter,&ch,1);
        for(int i=0;i<128;++i)
        {
            if (strcmp(dictionary[i],try_this_token) == 0)
            {
                printf("%c",i);
                memset(try_this_token,'\0',50);
                counter = -1;
                break;
            }
        }
        ++counter;
    }
    
    printf("\n");
    fclose(fp);
    free(try_this_token);
}

/* Create/Print the Huffman encodings, given a Huffman Tree
 * I actually ended up not using this. Dump to array has better functionality for this.
*/

void dump(HeapNode *node, int encoding[], int height)
{
    if(node->left)
    {
        encoding[height] = 0; //if we go left, the next bit is a 0
        dump(node->left,encoding,height+1); //continue down the tree
    }
    if(node->right)
    {
        encoding[height] = 1; //if we go left, the next bit is a 1
        dump(node->right,encoding,height+1); //continue down the tree
    }

    if(isLeaf(node))
    {
        printf("%c: ",node->vertex);
        for(int i=0;i<height;++i)
            printf("%d",encoding[i]);
        printf("\n");
    }
}

/* fills an array of strings, where array[i] holds the i'th ascii code encoding
 * Very Similar to dump
*/
void dump_to_array(HeapNode *node, char encoding[], int height, char **dictionary)
{
    if(node->left)
    {
        encoding[height] = '0'; //if we go left, the next bit is a 0
        dump_to_array(node->left,encoding,height+1,dictionary); //continue down the tree
    }
    if(node->right)
    {
        encoding[height] = '1'; //if we go right, the next bit is a 1
        dump_to_array(node->right,encoding,height+1,dictionary); //continue down the tree
    }

    if(isLeaf(node))
    {
        memcpy(dictionary[node->vertex],encoding,sizeof(char)*height); //copy the encoding into the right place in the dictionary
    }
}