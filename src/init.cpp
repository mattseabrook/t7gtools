// init.cpp

/*

Here we are going to initialize the game as per the DOSBox Debugger data referenced in README.md

*/

#include <string>
#include <vector>

struct Room {
	std::string name;
	std::string description;
	std::vector<std::string> items;
};

int main() {
	// More like current room instead of "house"
	// Header files to define each "room" ?
	
	std::vector<Room> house;

	Room room1;
	room1.name = "Foyer";
	room1.description = "You are in the foyer of the house. There is a door to the north and a door to the east.";
	room1.items.push_back("key");
	house.push_back(room1);

	Room room2;
	room2.name = "Dining Room";
	room2.description = "You are in the dining room. There is a door to the west and a door to the south.";
	room2.items.push_back("knife");
	house.push_back(room2);
/*
	Room room3;
	room3.name = "Kitchen";
	room3.description = "You are in the kitchen. There is a door to the north and a door to the east.";
	room3.items.push_back("rope");
	house.push_back(room3);

	Room room4;
	room4.name = "Library";
	room4.description = "You are in the library. There is a door to the west and a door to the south.";
	room4.items.push_back("book");
	house.push_back(room4);

	Room room5;
	room5.name = "Study";
	room5.description = "You are in the study. There is a door to the north and a door to the east.";
	room5.items.push_back("candle");
	house.push_back(room5);

	Room room6;
	room6.name = "Billiard Room";
	room6.description = "You are in the billiard room. There is a door to the west and a door to the south.";
	room6.items.push_back("pool cue");
	house.push_back(room6);

	Room room7;
	room7.name = "Ballroom";
	room7.description = "You are in the ballroom. There is a door to the north and a door to the east.";
	room7.items.push_back("piano");
	house.push_back(room7);

	Room room8;
	room8.name = "Conservatory";
	room8.description = "You are in the conservatory. There is a door to the west and a door to the south.";
	room8.items.push_back("flute");
	house.push_back(room8);

	Room room9;
	room9.name = "Gallery";
	room9.description = "You are in the gallery. There is a door to the north and a door to the east.";
	room9.items.push_back("painting");
	house.push_back(room9);

	Room room10;
	room10.name = "Bedroom";
	room10.description = "You are in the bedroom. There is a door to the west and a door to the south.";
	room10.items.push_back("bed");
	house.push_back(room10);

	Room room11;
	room11.name = "Bathroom";
	room11.description = "You are in the bathroom. There is a door to the north and a door to the east.";
	room11.items.push_back("shower");
	house.push_back(room11);

	Room room12;
	room12.name = "Attic";
	room12.description = "You are in the attic. There is a door to the west and a door to the south.";
	room12.items.push_back("doll");
	house.push_back(room12);

	Room room13;
	room13.name = "Basement";
	room13.description = "You are in the basement. There is a door to the north and a door to the east.";
	room13.items.push_back("cauldron");
	house.push_back(room13);

	Room room14;
	room14.name = "Cellar";
	room14.description = "You are in the cellar. There is a door to the west and a door to the south.";
	room14.items.push_back("wine");
	house.push_back(room14);

	Room room15;
	room15.name = "Secret Room";
	room15.description = "You are in the secret room. There is a door to the north and a door to the east.";
	room15.items.push_back("treasure");
	house.push_back(room15);
	*/
}