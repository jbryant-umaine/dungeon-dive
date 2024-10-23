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

struct Room *roomCreate(struct Room *room)
{
    struct Room *copy = malloc(sizeof(struct Room));

    strcpy(copy->name, room->name);
    strcpy(copy->code, room->code);
    strcpy(copy->description, room->description);
    copy->north = room->north;
    copy->east = room->east;
    copy->south = room->south;
    copy->west = room->west;

    return copy;
}
