//
// Created by eitan on 23/04/2022.
//
#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
struct RLEList_t{
    char nodeChar;
    int times;
    struct RLEList_t* next;
};
RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream== NULL)
    {
        printf("File is not available \n");
        return 0;
    }
    RLEList list_head = RLEListCreate();
    char letterToRead;
        while ((letterToRead = fgetc(in_stream)) != EOF)
        {
            if(RLEListAppend(list_head,letterToRead) != RLE_LIST_SUCCESS)
            {
                printf("Failed to append\n");
                return 0;
            }
        }
    return list_head;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(out_stream == NULL)
    {
        printf("File is not available \n");
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list == NULL)
    {
        printf("List is NULL \n");
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->times == 0)
    {
        return RLE_LIST_SUCCESS;
    }

    while (list != NULL)
    {
        while (list->times >1)
        {
            fputc(list->nodeChar, out_stream);
            list->times--;
        }
        fputc(list->nodeChar, out_stream);
        list= list->next;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(out_stream == NULL)
    {
        printf("File is not available \n");
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list == NULL)
    {
        printf("List is NULL \n");
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* stringToPrint = RLEListExportToString(list,&result);
    char* stringToDelete = stringToPrint;
    int i = 0;
    while (stringToPrint[i] != '\0')
    {
        fputc(stringToPrint[i], out_stream);
        i++;
    }
    //fputc('\0', out_stream);
    free(stringToDelete);
    return result;
}

