#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "minHeap.h"

int main()
{
    char *command = malloc(sizeof(char) * 100);
    char *commandaddress = command; //holds the original address of command since strtok changes it
    int *frequency = malloc(sizeof(int) * 128);
    MinHeap *heap;
    HeapNode *HuffmanTree;
    char **dictionary = malloc(sizeof(char*) * 128);
    for(int i=0;i<128;++i)
        dictionary[i] = malloc(sizeof(char) * 100);
    
    while (1)
    {
        //reset the buffer to the original address
        command = commandaddress;
        printf("Enter a command: import, encode, decode, dump, quit\n");
        fgets(command, 100, stdin);
        command = strtok(command," \n");
        
        if (strcmp(command,"import") == 0)
        {
            //reset stuff
            heap = create_heap(128);
            for(int i=0;i<128;++i)
            {
                frequency[i]=0;
                for(int j=0;j<50;++j)
                    dictionary[i][j] = '\0';
            }
            //get the filename
            command = strtok(NULL, " \n"); 
            //count how many times each char appears in the file
            create_frequency_array(command,frequency);
            //create the heap from this frequency array (128 for all 128 ascii chars)
            prepareHeap(heap, frequency, 128);
            //build the huffman tree
            HuffmanTree = buildHuffmanTree(heap);
            //dump the encodings into a dictionary
            char encoding[100]; int height = 0;
            dump_to_array(HuffmanTree,encoding,height,dictionary);
            //int encoding2[100]; int height2 = 0;
            //dump(HuffmanTree,encoding2,height2);
        }
        else if (strcmp(command,"encode") == 0)
        {
            //command now contains the filename
            command = strtok(NULL, " \n");
            encode_file(command,dictionary);
        }
        else if (strcmp(command,"decode") == 0)
        {
            //command now contains the filename
            command = strtok(NULL, " \n"); 
            decode_file(command,dictionary);
        }
        else if (strcmp(command,"dump") == 0)
        {
            for(int i=0;i<128;++i)
                printf("%c %s\n",i,dictionary[i]);
        }
        else if (strcmp(command,"quit") == 0)
        {
            break;
        }
        else //not valid command - give them options
        {
            printf("\n\n ^^^ That is not a valid command. Please enter one of the following\n\n");
            printf("import $filename$ - builds a huffman tree and its corresponding dictionary from the given file\n");
            printf("encode $filename$ - prints the encoded file in bits to stdout. Also prints the number of bits\n");
            printf("decode $filename$ - decodes a file containing a string of bits, and prints the decoded ascii to stdout\n");
            printf("dump - prints the dictionary to stdout\n");
            printf("quit - quits the program and returns to the command line\n\n");
        }
    }

    for(int i=0;i<128;++i)
        free(dictionary[i]);
    free(dictionary);
    free(heap->pos);
    free(heap);
    free(commandaddress);
    free(frequency);
    return 0;
}