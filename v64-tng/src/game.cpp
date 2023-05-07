// game.cpp

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "game.h"

// Portable function to read a single character from the console
// Removed after debugging
char getch()
{
    char ch;
    std::cin.get(ch);
    return ch;
}

/* ============================================================================
                                  gameLoop

   Description:
     This function is the main game loop, responsible for handling the game
     state and user input for The 7th Guest. It initializes the current room
     as the FOYER and then repeatedly updates the game state based on user
     input. The loop continues until the player decides to exit the game by
     pressing 'X' or 'ESC' key. The game state is currently represented by the
     current room the player is in, and the player can navigate between rooms
     using the left and right arrow keys. The room information is printed to
     the console for debugging purposes.

   ============================================================================
*/
void gameLoop()
{
    Room current_room = Room::FOYER;

    while (true)
    {
        std::string current_rl_filename = getRoomRLFilename(current_room);
        std::cout << "Current room: " << static_cast<int>(current_room) << " (" << current_rl_filename << ")" << std::endl;

        if (current_room == Room::DINING_ROOM)
        {
            // Do something specific for the Dining Room
            std::cout << "Welcome to the Dining Room!" << std::endl;
        }

        char ch = getch();

        if (ch == 'x' || ch == 'X' || ch == '\033') // Exit the game
        {
            break;
        }
        else if (ch == '\x1b' && std::cin.get() == '[') // Arrow key
        {
            ch = std::cin.get();

            switch (ch)
            {
            case 'C': // Right arrow key
                current_room = static_cast<Room>((static_cast<int>(current_room) + 1) % static_cast<int>(Room::ALTAR) + 1);
                break;
            case 'D': // Left arrow key
                current_room = static_cast<Room>((static_cast<int>(current_room) - 1) % static_cast<int>(Room::ALTAR) + 1);
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}