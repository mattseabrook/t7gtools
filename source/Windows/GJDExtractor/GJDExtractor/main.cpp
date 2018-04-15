// main.cpp

#include <iostream>

#include "cli.h"
#include "RLFile.h"

int main(int argc, char *argv[])
{
	std::cout << EXE_NAME << " v" << VER_NUM << " - Binary/Resource Utility for The 7th Guest" << std::endl
		<< "(c) 2018 Matt Seabrook - info@mattseabrook.net"
		<< "\r\n"
		<< std::endl;

	CLI arguments;

	if (argv[1] != NULL)
	{
		switch (switchProc(argv[1]))
		{
		case VERSION:
		{
			arguments.verInfo();
			return 0;
		}
		case HELP:
		{
			arguments.helpText();
			return 0;
		}
		case RLFILE:
		{
			RLFile rlfile;

			rlfile.open(argv[2]);

			return 0;
		}
		default:
		{
			std::cout << "ERROR: Unrecognized switch: '"
				<< argv[1]
				<< "', please see --help for more information:"
				<< "\r\n"
				<< std::endl;

			arguments.helpText();

			break;
		}
		}
	}
	else
	{
		arguments.helpText();
	}

	return 0;
}