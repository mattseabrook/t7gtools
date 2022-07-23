// main.cpp
#include <iostream>

#include "gui.h"

int main(int argc, char* argv[])
{
	// Replace this with Mall World project code
	if ((strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0))
	{
		// Test remove later
		std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
	}
	else if ((strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-about") == 0))
	{
		openWindow();
	}
	
	return 0;
}