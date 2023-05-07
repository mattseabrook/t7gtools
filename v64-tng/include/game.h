// game.h

#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

/*
===============================================================================

    7th Guest - Game.h

    This header file contains the enum class and function prototype to map
    room names to RL filenames, as well as game state.

===============================================================================
*/

enum class Room
{
    FOYER,
    LIBRARY,
    DINING_ROOM,
    KITCHEN,
    GAME_ROOM,
    HALLWAY,
    BEDROOM,
    BATHROOM,
    MUSIC_ROOM,
    ALTAR,
    // ... other rooms or special locations
};

const std::map<Room, std::string> ROOM_DATA = {
    {Room::DINING_ROOM, "DR.RL"},
    // Add more rooms here
};

std::string getRoomRLFilename(Room room);
void gameLoop();

#endif // GAME_H