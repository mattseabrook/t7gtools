// main.cpp

#include <iostream>


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
	CLI::tagLine();

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
			RLFile::open(argv[2]);

			return 0;
		}
		case TEST:
		{
			//...
			std::cout << "Nothing right now.";

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

	//CLI::helpText();

	return 0;
}