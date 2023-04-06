//
// Created by eitan on 23/04/2022.
//
#include "RLEList.h"
#ifndef TOOL_ASCIIARTTOOL_H
#define TOOL_ASCIIARTTOOL_H

/**
 * The function reads the given file and compresses it using the RLE method.
 * @param in_stream  - FILE* type object that contains the image you want to compress.
 * @return A list in type RLEList that contains all the characters in the image.
 */
RLEList asciiArtRead(FILE* in_stream);

/**
 * The function writes an image that is represented by a list of type RLEList to a file.
Parameters:
 * @param list - A list of the RLEList type that contains all the characters in the image.
 * @param out_stream - An object of type * FILE to which we will write the image.
 * @return RLEListResult :
 * RLE_LIST_NULL_ARGUMENT - when one param is NULL
 * RLE_LIST_SUCCESS when success
 */

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
/**
 * The function writes the image to the file in a compressed form (in a format returned from RLEListExportToString.)
Parameters:
 * @param list - a list of the RLEList type that contains the characters in the image.
 * @param out_stream - an object of type * FILE to which we will write the compressed image.
 * @return RLEListResult:
 * RLE_LIST_NULL_ARGUMENT - when one of the parametes is NULL
 * SUCCESS_LIST_RLE - when success
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif // TOOL_ASCIIARTTOOL_H
