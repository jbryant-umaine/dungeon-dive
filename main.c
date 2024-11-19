#include <stdio.h>
#include "stringManip.h"
#include "roomManip.h"
#include <time.h>

/*
createDungeon: Takes the pointer to the room array, the size of the room array, and the size of the dungeon to be created. Returns back a pointer to the first room of the “dungeon”.
This will look at the room array and pick a random “room” for each room in the dungeon. Aka, create a copy of the room then add it to the linked list.
For now, only make the dungeon a 2d linked list. Make sure it’s bi-directional (you can go both east and west).
*/
Room *createDungeon(Room *rooms, int sizeOfRooms, int dungeonGridSize)
{
    srand(time(0));

    Room *grid[dungeonGridSize][dungeonGridSize];
    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < dungeonGridSize; i++)
    {
        for (int j = 0; j < dungeonGridSize; j++)
        {
            int n = rand() % sizeOfRooms;

            Room *newRoom = roomCreate(&rooms[n]);
            grid[i][j] = newRoom;

            // Connect to the room to the west
            if (j > 0)
            {
                newRoom->West = grid[i][j - 1];
                grid[i][j - 1]->East = newRoom;
            }

            // Connect to the room to the north
            if (i > 0)
            {
                newRoom->North = grid[i - 1][j];
                grid[i - 1][j]->South = newRoom;
            }
        }
    }

    return grid[0][0]; // Return the head of the dungeon
}

void deleteDungeon(Room *dungeon)
{
    Room *current = dungeon;
    Room *nextNode;
    while (current)
    {
        nextNode = current->East;
        free(current);
        current = nextNode;
    }
}

void printDungeon(Room *dungeon, int dungeonGridSize)
{
    Room *row = dungeon; // Start at head of the dungeon)
    while (row != NULL)
    {
        Room *current = row; // Traverse each row
        while (current != NULL)
        {
            printf("%s ", current->code);
            current = current->East; // Move to the next room in row
        }
        printf("\n");
        row = row->South; // Move down a row
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

    Room *rooms = readRoomFile(argv[1], roomSize);

    char buffer[256];

    int dungeonGridSize = 0;

    printf("Enter dungeon grid size: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        dungeonGridSize = atoi(buffer);
    }

    if (dungeonGridSize == 0)
    {
        printf("Invalid dungeon count.\n");
        return 0;
    }

    printf("\n");

    Room *dungeon = createDungeon(rooms, *roomSize, dungeonGridSize);

    printDungeon(dungeon, dungeonGridSize);

    // deleteDungeon(dungeon);

    dungeon = NULL;

    return 0;
}