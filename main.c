#include <stdio.h>
#include "stringManip.h"

int main()
{
    char *testWsRemove = str_trim("     hello");
    printf("Whitespace removal: %s\n", testWsRemove);

    char *testStrCut = str_cut("hello", 2, 4);
    printf("String substring: %s\n", testStrCut);
}