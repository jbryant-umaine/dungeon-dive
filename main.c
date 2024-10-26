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
    srand(time(0));

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
    int *roomSize = malloc(sizeof(int));

    struct Room *rooms = readRoomFile(argv[1], roomSize);

    char buffer[256];
    int num = 0;

    printf("Enter dungeon size: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        num = atoi(buffer);
    }

    printf("\n");

    struct Room *dungeons = createDungeon(rooms, *roomSize, num);

    printDungeon(dungeons);

    deleteDungeon(dungeons);

    return 0;
}