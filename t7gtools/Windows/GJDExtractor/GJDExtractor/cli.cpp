// cli.cpp

#include <iostream>
#include <windows.h>

#include "cli.h"

/*
=====================================================
switchProc
Function to enumerate the User-defined CLI switches
=====================================================
*/
Options switchProc(std::string Q)
{
	if (Q == "-r" || Q == "--rlfile")
		return RLFILE;
	if (Q == "-h" || Q == "--help")
		return HELP;
	if (Q == "-t" || Q == "--test")
		return TEST;
	if (Q == "-v" || Q == "--version")
		return VERSION;
	return INVALID;
}

/*
=============================================
tagLine
Function to write the CLI tag line
=============================================
*/
void CLI::tagLine()
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
}


/*
==============================================
verInfo
Function to display version/tool information
==============================================
*/
void CLI::verInfo()
{
	//...
}