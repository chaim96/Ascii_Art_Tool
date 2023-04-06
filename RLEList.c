#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "RLEList.h"


struct RLEList_t{
    char nodeChar;
    int times;
    struct RLEList_t* next;
};


RLEList RLEListCreate(){
        RLEList headRLEList = malloc(sizeof(*headRLEList));
        if (headRLEList == NULL)
        {
            return NULL;
        }
        headRLEList->times = 0;
        headRLEList->next = NULL;
        return headRLEList;
}

void RLEListDestroy(RLEList list) {
    while (list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

/**
*   RLEListAppend: add a specified character at the end of the list.
*
* @param list - The RLE list for which to add the character
* @param value - The character which needs to be added.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_OUT_OF_MEMORY if an allocation failed
* 	RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult RLEListAppend(RLEList list, char value){
    // check if in the end list (head) doesnt point to head
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->next == NULL && list->times <1)
    {
            list->nodeChar = value;
            list->times = 1;
            return RLE_LIST_SUCCESS;
    }
    while (list->next != NULL)
    {
        list = list->next;
    }
    if (value == list->nodeChar)
    {
        list->times++;
    }
    else {
        RLEList newNode = RLEListCreate();
        if (newNode == NULL) {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->nodeChar = value;
        newNode->times = 1;
        newNode->next = NULL;
        list->next = newNode;
    }
    return RLE_LIST_SUCCESS;
}
/**
* RLEListSize: Returns the total number of characters in an RLE list.
* @param list - The RLE list whose size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the total number of characters in the list.
*/
int RLEListSize(RLEList list)
{
    int size = 0;
    if (!list)
    {
        return -1;
    }
    while (list)
    {
        //to cheack that
        size += list->times;
        list = list->next;
    }
    return size;
}

/**
*   RLEListRemove: Removes a character found at a specified index in an RLE list.
*
* @param list - The RLE list to remove the character from.
* @param index - The index at which the character to be removed is found.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	RLE_LIST_SUCCESS the character found at index has been removed successfully.
*/
void RemoveNode(RLEList list, int place, RLEList formerNode, int listSize)
{
    if(place == 1)
    {
        if (list->times > 1)
        {
            list->times--;
        }
        else {
            RLEList nextNode;
            while (list->next) {
                nextNode = list->next;
                list->nodeChar = nextNode->nodeChar;
                list->times = nextNode->times;
                formerNode = list;
                list = list->next;
            }

            if (listSize > 1)
            {
                free(list);
                formerNode->next = NULL;
            }
            else //first node is single and needs to be rebooted
            {
                list->nodeChar = '\0';
                list->times = 0;
                list->next = NULL;
            }
        }
    }
    else
    {
        if (place == listSize)
        {
            if (list->times > 1)
            {
                list->times--;
            }
            else
            {
                formerNode->next = NULL;
                free(list);
            }
        }
        else
        {
           if (list->times > 1)
           {
                list->times--;
           }
           else
           {
               formerNode->next = list->next;
               free(list);
           }
        }
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    int placeForLoop = index+1;
    int placeOriginal = index+1;
    // To check if index is starting form zero
    RLEList formerNode;
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    if(placeOriginal > listSize || placeOriginal < 1)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    while (list != NULL)
    {
        if (placeForLoop - list->times <= 0)
        {
            RemoveNode(list, placeOriginal, formerNode, listSize);
            return RLE_LIST_SUCCESS;
        }
        else
        {
            placeForLoop -= list->times;
            formerNode = list;
            list = list->next;
        }
    }
    return RLE_LIST_ERROR;
}

/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	0 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.
*/
char RLEListGet(RLEList list, int index, RLEListResult* result)
{
    int place = index+1;
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
   if (place > RLEListSize(list) || place < 1)
   {
       if (result != NULL)
       {
           *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
       }
       return 0;
   }
    while (list)
    {
        if (place - list->times <= 0)
        {
            if (result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return list->nodeChar;
        }
        else
        {
            place -= list->times;
            list = list->next;
        }
    }
    return RLE_LIST_ERROR;
}


/**
*   RLEListExportToString: Returns the characters found in an RLE list as a string.
*
* @param list - The RLE list to be exported as a string.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	LIST_SUCCESS the RLE list has been successfuly exported as a string.
* @return
* 	NULL if result is not RLE_LIST_SUCCESS.
* 	The string that corresponds to the received RLE list.
*/
int numOfDigits (int num)
{
    int counter = 0;
    while (num != 0)
    {
        counter++;
        num = num /10;
    }
    return  counter;
}

int inverseNumber (int num)
{
    int remainder, inverse=0;
    while (num != 0) {
        remainder = num % 10;
        inverse = inverse * 10 + remainder;
        num /= 10;
    }
    return inverse;
}

int RLEListExportToStringStringSize (RLEList list)
{
    int stringSize = 1; // we start with one becuse '/0'
    while (list)
    {
        stringSize ++; // we add one for size because list->nodeChar
        stringSize += numOfDigits(list->times); // we add  for size the size of list->times
        stringSize ++; // we add one becuse '/n'
        list = list->next;
    }
    return  stringSize;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int stringSize = RLEListExportToStringStringSize(list);
    if (stringSize == 1 && list->times==0)
    {
        return NULL;
    }
    int i=0;
    int inverseTimes;
    char* stringToPrint = calloc(sizeof(char) *stringSize, sizeof(char));
    if (stringToPrint == NULL)
    {
        if (result != NULL)
        {
        *result = RLE_LIST_ERROR;
        }
        return NULL;
    }
    else
    {
        while((i<stringSize-1) && list)
        {
            stringToPrint[i] = list->nodeChar;
            inverseTimes = inverseNumber((list->times));
            for (int j=0; j<numOfDigits(list->times); j++)
            {
                stringToPrint[++i] = inverseTimes%10 + '0';
                inverseTimes /= 10;
            }
            stringToPrint[++i] = '\n';
            list = list->next;
            i++;
        }
        stringToPrint[i] = '\0';
        if (result != NULL)
        {
        *result = RLE_LIST_SUCCESS;
        }
        return stringToPrint;
    }
}

/**
*   RLEListMap: Change the given RLE list's characters according to the received mapping function.
*               This function replaces each character of the give RLE list with its mapped character.
*
* @param list - The RLE list to edit.
* @param MapFunction - Pointer to a function of type MapFunction.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS if the mapping is done successfully.
*/
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->times == 0)
    {
        return RLE_LIST_SUCCESS;
    }
    while (list != NULL)
    {
        list->nodeChar = map_function(list->nodeChar);
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}