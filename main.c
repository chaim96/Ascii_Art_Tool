#include <stdio.h>
#include <string.h>
#include "AsciiArtTool.h"
#include "RLEList.h"
#include <assert.h>

#define FLAG_1 "-e"
#define FLAG_2 "-i"
#define SOURCE_ARGUMENT 2
#define TARGET_ARGUMENT 3


char AsciiArtInverted(char s)  //Inverting '@' to ' ' and inverse
{
    if (s == ' ')
    {
        return '@';
    }
    if (s == '@')
    {
        return ' ';
    }
    return s;
}

/* main.c */
int main(int argc, char *argv[])
{
    char const* source = argv[SOURCE_ARGUMENT];
    char const* dest = argv[TARGET_ARGUMENT];
    if(argc > 1 && (strcmp(argv[1], FLAG_1) == 0)) //Return value = 0 then it indicates str1 is equal to str2.
    {
        RLEListResult result;
        RLEList list_head;
        FILE *fpSource;
        FILE *fpTarget;
        fpSource = fopen(source, "r");
        list_head = asciiArtRead(fpSource);
        fclose(fpSource);
        fpTarget = fopen(dest, "w");
        result = asciiArtPrintEncoded(list_head,fpTarget);
        if(result == RLE_LIST_SUCCESS)
            {
            ;
            }
        assert(result == RLE_LIST_SUCCESS);
        RLEListDestroy(list_head);
        fclose(fpTarget);
    }
    if(argc > 1 && (strcmp(argv[1], FLAG_2) == 0)) //Return value = 0 then it indicates str1 is equal to str2.
    {
        RLEListResult result;
        RLEList list_head;
        FILE *fpSource;
        FILE *fpTarget;
        fpSource = fopen(source, "r");
        list_head = asciiArtRead(fpSource);
        fclose(fpSource);
        result = RLEListMap(list_head, AsciiArtInverted);
        if(result == RLE_LIST_SUCCESS)
            {
            ;
            }
        assert(result == RLE_LIST_SUCCESS);
        fpTarget = fopen(dest, "w");
        result = asciiArtPrint(list_head, fpTarget);
        if(result == RLE_LIST_SUCCESS)
            {
            ;
            }
        assert(result == RLE_LIST_SUCCESS);
        RLEListDestroy(list_head);
        fclose(fpTarget);
    }
    return 0;
}