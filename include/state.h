// state.h

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include <map>

//===========================================================================

struct GameState
{
    int currentRoom;                  // the ID of the current room
    std::vector<bool> completedRooms; // a vector of boolean values indicating which rooms have been completed
    
    // Enumeration to represent the room IDs
    enum RoomID {
        FOYER = 0,
        DINING_ROOM = 1,
        LIBRARY = 2,
        // ...
        NUM_ROOMS = 22
    };

    // Mapping between room IDs and room names
    static const std::map<RoomID, std::string> ROOM_NAMES;

    // Constructor to initialize the game state
    GameState(int startingRoom, int numRooms);

    // Function to mark a room as completed
    void completeRoom(int roomID);

    // Function to check if a room is completed
    bool isRoomCompleted(int roomID) const;
};

//===========================================================================

#endif // STATE_H