#ifndef ROOM_MANIP_H
#define ROOM_MANIP_H

#include "stringManip.h"

typedef struct Room Room;

// Room struct that defines required data.
struct Room
{
    char name[50];
    char code[3];
    char description[500];
    Room *North;
    Room *East;
    Room *South;
    Room *West;
};

// Function prototypes
Room *roomCreate(Room *room);
Room *readRoomFile(char *fileName, int *roomSize);

#endif