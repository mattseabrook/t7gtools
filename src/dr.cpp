// dr.cpp

/*

	Dining Room

*/

#include <string>
#include <vector>

#include <fstream>

struct Room {
	std::string name;
	std::string description;
	std::vector<std::string> items;
};

int test() {
	// Open a binary file in the local directory named 'dr.rl'
	std::ifstream input("dr.rl", std::ios::binary);
	if (!input) {
		//std::cout << "Error: could not open file" << std::endl;
		return 1;
	}

	// Grab the first 20  bytes only of 'input' and store it in a char array
	char buffer[20];
	input.read(buffer, 20);
}