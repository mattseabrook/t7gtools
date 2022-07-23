// main.cpp
#include <iostream>

int main(int argc, char* argv[])
{
	// test if argv[1] is "-h" or "-help, and if it is, print the help message and exit
	if ((strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0))
	{
		std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 0;
	}
	else if ((strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-about") == 0))
	{
		// Open a window that is 1280x720 that contains a text string that says "About"
		// The text string should be centered in the window.
		// The window should be titled "About"
		// The window should be a top-level window
		// The window should be a modal window
		// The window should be a window that is not resizable
		// The window should be a window that is not minimizable
		// The window should be a window that is not maximizable
		
		return 0;
		
	}
}