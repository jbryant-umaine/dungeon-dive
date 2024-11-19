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

    Room *currentRoom = dungeon;

    printDungeon(dungeon, dungeonGridSize);

    printf("\n");

    while (1)
    {
        /*
        Display the room description of the room you’re in (start at the head)
        Display list of available exists
        Ask the user for a command
        Process/act on the command
        */
        printf("<Current Room: %s>\n", currentRoom->name);
        printf("Description: %s\n\n", currentRoom->description);
        printf("Available exits:\n");
        if (currentRoom->North)
        {
            printf("\t- North: %s\n", currentRoom->North->name);
        }
        if (currentRoom->East)
        {
            printf("\t- East: %s\n", currentRoom->East->name);
        }
        if (currentRoom->South)
        {
            printf("\t- South: %s\n", currentRoom->South->name);
        }
        if (currentRoom->West)
        {
            printf("\t- West: %s\n", currentRoom->West->name);
        }

        char buffer[256];

        printf("\ncommand: ");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            char *command = str_cut(buffer, 0, 5);
            command = str_trim(command);

            printf("\n");

            if (strncmp("move", command, strlen("move")) == 0)
            {
                char direction = buffer[5];
                switch (direction)
                {
                case 'N':
                case 'n':
                    if (currentRoom->North)
                        currentRoom = currentRoom->North;
                    else
                        printf("You bump into a wall!\n");
                    break;
                case 'E':
                case 'e':
                    if (currentRoom->East)
                        currentRoom = currentRoom->East;
                    else
                        printf("You bump into a wall!\n");
                    break;
                case 'S':
                case 's':
                    if (currentRoom->South)
                        currentRoom = currentRoom->South;
                    else
                        printf("You bump into a wall!\n");
                    break;
                case 'W':
                case 'w':
                    if (currentRoom->West)
                        currentRoom = currentRoom->West;
                    else
                        printf("You bump into a wall!\n");
                    break;
                default:
                    printf("Invalid direction. Options: <n,e,s,w>\n");
                }
                printf("\n");
                continue;
            }

            if (strncmp("exit", command, strlen("exit")) == 0)
            {
                printf("Exiting dungeon...\n");
                break;
            }

            printf("Invalid command. (options: move <n,e,s,w>, exit)\n\n");
        }
    }

    deleteDungeon(dungeon, dungeonGridSize);

    dungeon = NULL;

    return 0;
}