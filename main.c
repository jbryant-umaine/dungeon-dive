#include <stdio.h>
#include "stringManip.h"
#include "roomManip.h"

int main(int argc, char *argv[])
{
    char *testWsRemove = str_trim("     hello");
    printf("Whitespace removal: %s\n", testWsRemove);

    char *testStrCut = str_cut("AA", 0, 2);
    char *testWsRmv = str_trim(testStrCut);
    printf("String substring: %s\n", testWsRmv);

    int *roomSize;

    struct Room *rooms = readRoomFile(argv[1], roomSize);

    return 0;
}