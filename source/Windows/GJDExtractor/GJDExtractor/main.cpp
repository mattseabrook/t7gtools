// main.cpp

#include <iostream>
#include <windows.h>

#include "cli.h"
#include "RLFile.h"


/*
==============================================
main

Process CLI arguments
==============================================
*/
int main(int argc, char *argv[])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Banner
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "\"\"8\"\" ";

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "eeeee";

	SetConsoleTextAttribute(hConsole, 13);
	std::cout << " 8\"\"\"\"8                               \n"
		"  8   ";

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "8   8 ";

	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "8    \" eeeee eeeee eeeee e     eeeee \n"
		"  8e     ";

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "e' ";

	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "8e       8   8  88 8  88 8     8   \" \n"
		"  88    ";

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "e'  ";
	
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "88  ee   8e  8   8 8   8 8e    8eeee \n"
		"  88    ";
	
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "8   ";
	
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "88   8   88  8   8 8   8 88       88 \n"
		"  88    ";
	
	SetConsoleTextAttribute(hConsole, 12); 
	std::cout << "8   ";
	
	SetConsoleTextAttribute(hConsole, 13); 
	std::cout << "88eee8   88  8eee8 8eee8 88eee 8ee88\n";


	// Tag line
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << EXE_NAME << " v" << VER_NUM << " - Binary/Resource Utility for The 7th Guest" << std::endl
		<< "(c) 2018 Matt Seabrook - info@mattseabrook.net"
		<< "\r\n"
		<< std::endl;

	SetConsoleTextAttribute(hConsole, 7);

	if (argv[1] != NULL)
	{
		switch (switchProc(argv[1]))
		{
		case VERSION:
		{
			CLI::verInfo();

			return 0;
		}
		case HELP:
		{
			break;
		}
		case RLFILE:
		{
			// Input validation to prevent opening of any other file type

			RLFile::open(argv[2]);

			return 0;
		}
		case TEST:
		{
			for (int k = 1; k < 255; k++)
			{
				// pick the colorattribute k you want
				SetConsoleTextAttribute(hConsole, k);
				std::cout << k << " I want to be nice today!" << std::endl;
			}

			return 0;
		}
		default:
		{
			std::cout << "ERROR: Unrecognized switch: '"
				<< argv[1]
				<< "', please see --help for more information:"
				<< "\r\n"
				<< std::endl;

			break;
		}
		}
	}

	CLI::helpText();

	return 0;
}