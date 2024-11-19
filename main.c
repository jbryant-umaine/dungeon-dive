#include <stdio.h>
#include "stringManip.h"
#include "roomManip.h"
#include <time.h>

/**
 * Creates a dungeon which is a 2D array filled with a random selection of rooms. Returns the head of the dungeon.
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

/**
 * Loops through each room in the dungeon grid and frees the memory of each one.
 */
void deleteDungeon(Room *dungeon, int dungeonGridSize)
{
    Room *row = dungeon;

    while (row != NULL)
    {
        Room *current = row;
        Room *nextRow = row->South;
        while (current != NULL)
        {
            Room *nextRoom = current->East;
            free(current);
            current = nextRoom;
        }
        row = nextRow;
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

    deleteDungeon(dungeon, dungeonGridSize);

    dungeon = NULL;

    return 0;
}