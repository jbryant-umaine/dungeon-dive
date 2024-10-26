#ifndef ROOM_MANIP_H
#define ROOM_MANIP_H

#include "stringManip.h"

// Room struct that defines required data.
struct Room
{
    char name[50];
    char code[3];
    char description[500];
    struct Room *north;
    struct Room *east;
    struct Room *south;
    struct Room *west;
};

// Function prototypes
struct Room *roomCreate(struct Room *room);
struct Room *readRoomFile(char *fileName, int *roomSize);

#endif