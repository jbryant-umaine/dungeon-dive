#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roomManip.h"

Room *roomCreate(Room *room)
{
    Room *r = malloc(sizeof(Room));
    *r = *room;

    return r;
}

Room *readRoomFile(char *fileName, int *roomSize)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("File could not be opened.\n");
        exit(1);
    }

    // Keep track of how many rooms along with which property.
    int roomCount = 0;
    int roomProperty = 0;

    // Allocate memory for one room.
    Room *rooms = malloc(sizeof(Room));

    char line[1000];

    // Read file line by line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Ignore empty lines
        if (line[0] == '\n')
        {
            roomProperty = 0;
            continue;
        }

        // Room name
        if (roomProperty == 0)
        {
            char *name = str_cut(line, 11, strlen(line) - 1);
            char *trimmedName = str_trim(name);

            strcpy(rooms[roomCount].name, trimmedName);

            free(name);
            free(trimmedName);

            roomProperty++;
            continue;
        }

        // Room code
        if (roomProperty == 1)
        {
            // Copy room code
            char *code = str_cut(line, 11, strlen(line) - 1);

            char *trimmedCode = str_trim(code);

            strcpy(rooms[roomCount].code, trimmedCode);

            free(code);
            free(trimmedCode);

            roomProperty++;
            continue;
        }

        // Room desc
        if (roomProperty == 2)
        {
            char *desc = str_cut(line, 18, strlen(line) - 1);
            char *trimmedDesc = str_trim(desc);

            strcpy(rooms[roomCount].description, trimmedDesc);

            free(desc);
            free(trimmedDesc);

            roomCount++;

            Room *temp = realloc(rooms, (roomCount + 1) * sizeof(struct Room));

            roomProperty = 0;

            rooms = temp;
        }
    }

    fclose(fp);

    *roomSize = roomCount;

    return rooms;
}