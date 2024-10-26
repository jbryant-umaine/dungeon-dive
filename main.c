#include <stdio.h>
#include "stringManip.h"
#include "roomManip.h"
#include <time.h>

/*
createDungeon: Takes the pointer to the room array, the size of the room array, and the size of the dungeon to be created. Returns back a pointer to the first room of the “dungeon”.
This will look at the room array and pick a random “room” for each room in the dungeon. Aka, create a copy of the room then add it to the linked list.
For now, only make the dungeon a 2d linked list. Make sure it’s bi-directional (you can go both east and west).
*/
struct Room *createDungeon(struct Room *rooms, int sizeOfRooms, int sizeOfDungeons)
{
    struct Room *dungeons = malloc(sizeof(struct Room) * sizeOfDungeons);

    struct Room *previous = NULL;

    for (int i = 0; i < sizeOfDungeons; i++)
    {
        int r = rand();
        int n = r % sizeOfRooms;

        dungeons[i] = *roomCreate(&rooms[n]);

        if (previous != NULL)
        {
            previous->east = &dungeons[i];
            dungeons[i].west = previous;
        }

        previous = &dungeons[i];
    }

    return dungeons;
}

void deleteDungeon(struct Room *dungeons)
{
    free(dungeons);
}

void printDungeon(struct Room *dungeons)
{
    struct Room *temp = dungeons;

    while (1)
    {
        printf("Room %s: %s\n", temp->code, temp->name);

        if (temp->east == NULL)
        {
            break;
        }

        temp = temp->east;
    }
}

int main(int argc, char *argv[])
{
    char *testWsRemove = str_trim("     hello");
    printf("Whitespace removal: %s\n", testWsRemove);

    char *testStrCut = str_cut("AA", 0, 2);
    char *testWsRmv = str_trim(testStrCut);
    printf("String substring: %s\n", testWsRmv);

    int *roomSize = malloc(sizeof(int));

    struct Room *rooms = readRoomFile(argv[1], roomSize);

    struct Room *dungeons = createDungeon(rooms, *roomSize, 10);

    printDungeon(dungeons);

    return 0;
}