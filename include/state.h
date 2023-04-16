// state.h

#ifndef STATE_H
#define STATE_H

#include <vector>

//===========================================================================

struct GameState
{
    int currentRoom;                  // the ID of the current room
    std::vector<bool> completedRooms; // a vector of boolean values indicating which rooms have been completed

    // Constructor to initialize the game state
    GameState(int startingRoom, int numRooms);

    // Function to mark a room as completed
    void completeRoom(int roomID);

    // Function to check if a room is completed
    bool isRoomCompleted(int roomID) const;
};

//===========================================================================

#endif // STATE_H