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

    int *roomSize = malloc(sizeof(int));

    struct Room *rooms = readRoomFile(argv[1], roomSize);

    for (int i = 0; i < *roomSize; i++)
    {
        printf("Room Name: %s\n", rooms[i].name);
        printf("Room Code: %s\n", rooms[i].code);
        printf("Room Desc: %s\n", rooms[i].description);
    }

    return 0;
}