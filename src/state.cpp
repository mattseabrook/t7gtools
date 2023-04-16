// state.cpp

/*

    Game State

*/

#include <vector>

struct GameState {
    int currentRoom;  // the ID of the current room
    std::vector<bool> completedRooms;  // a vector of boolean values indicating which rooms have been completed

    // Constructor to initialize the game state
    GameState(int startingRoom, int numRooms) : currentRoom(startingRoom), completedRooms(numRooms, false) {}

    // Function to mark a room as completed
    void completeRoom(int roomID) {
        if (roomID >= 0 && roomID < completedRooms.size()) {
            completedRooms[roomID] = true;
        }
    }

    // Function to check if a room is completed
    bool isRoomCompleted(int roomID) const {
        if (roomID >= 0 && roomID < completedRooms.size()) {
            return completedRooms[roomID];
        }
        return false;
    }
};
