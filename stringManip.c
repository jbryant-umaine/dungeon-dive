#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringManip.h"

/*
stringManip.c: Contains any function related to string manipulation such as
str_trim: removes the whitespace from each end of a string sent to it, returning a pointer to the new string
str_cut: takes three arguments, the string pointer, an integer representing the start, and an integer representing the end. Returns a pointer to the substring that begins at the start and ends at the end.
*/

char *str_cut(char charString[], int start, int end)
{
    // Create string with capacity of start to end index
    char *trimmedString = malloc((end - start + 2) * sizeof(char));

    // Copy first to last index into new string
    strncpy(trimmedString, &charString[start], end - start + 1);
    trimmedString[end - start + 1] = '\0';

    return trimmedString;
}

char *str_trim(char charString[])
{

    int start = 0, end = strlen(charString) - 1;

    // Calculate index of first non-whitespace character
    while (charString[start] == ' ')
    {
        start++;
    }

    // Calculate index of last non-whitespace character
    while (charString[end] == ' ')
    {
        if (end == start)
            break;
        end--;
    }

    return str_cut(charString, start, end);
}