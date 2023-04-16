// init.cpp

/*

Here we are going to initialize the game as per the DOSBox Debugger data referenced in README.md

*/
#include "xmi.h"

int init() {
	if (!loadMusic())
		return -1;
}



/*

// Get the name of the current room
std::string currentRoomName = GameState::ROOM_NAMES.at(gameState.currentRoom);
std::cout << "Current room: " << currentRoomName << std::endl;

// Get the name of a completed room
int roomID = 1;
if (gameState.isRoomCompleted(roomID)) {
    std::string roomName = GameState::ROOM_NAMES.at(roomID);
    std::cout << "Room " << roomID << " completed: " << roomName << std::endl;
}






init game state in main example:

			#include "state.h"

			int main() {
				// Create a new game state with starting room ID 0 and 22 total rooms
				GameState gameState(0, 22);

				// Access the current room ID and completed room data
				int currentRoom = gameState.currentRoom;
				std::vector<bool> completedRooms = gameState.completedRooms;

				// Update the game state by completing a room
				gameState.completeRoom(3);

				// Check if a room is completed
				bool roomCompleted = gameState.isRoomCompleted(3);
				
				// ...
				
				return 0;
			}


*/