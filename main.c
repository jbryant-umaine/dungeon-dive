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

    struct Room *head = NULL;
    struct Room *current = NULL;

    for (int i = 0; i < sizeOfDungeons; i++)
    {
        int n = rand() % sizeOfRooms;

        struct Room *newRoom = roomCreate(&rooms[n]);

        if (head == NULL)
        {
            head = newRoom;
            current = head;
        }
        else
        {
            current->East = newRoom;
            newRoom->West = current;
            current = newRoom;
        }
    }

    return head;
}

void deleteDungeon(struct Room *dungeon)
{
    struct Room *current = dungeon;
    struct Room *nextNode;
    while (current)
    {
        nextNode = current->East;
        free(current);
        current = nextNode;
    }
}

void printDungeon(struct Room *dungeons)
{
    struct Room *temp = dungeons;

    while (1)
    {
        printf("Room %s: %s\n", temp->code, temp->name);

        if (temp->East == NULL)
        {
            break;
        }

        temp = temp->East;
    }
}

int main(int argc, char *argv[])
{
    int *roomSize = malloc(sizeof(int));

    if (argc != 2)
    {
        printf("Invalid argument count. Must supply path to a text file.\n");
        return 0;
    }

    struct Room *rooms = readRoomFile(argv[1], roomSize);

    char buffer[256];
    int num = 0;

    printf("Enter dungeon size: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        num = atoi(buffer);
    }

    if (num == 0)
    {
        printf("Invalid dungeon count.\n");
        return 0;
    }

    printf("\n");

    struct Room *dungeon = createDungeon(rooms, *roomSize, num);

    printDungeon(dungeon);

    deleteDungeon(dungeon);

    dungeon = NULL;

    return 0;
}