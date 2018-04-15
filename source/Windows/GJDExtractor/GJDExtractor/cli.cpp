// cli.cpp

#include <iostream>
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
	if (Q == "-v" || Q == "--version")
		return VERSION;
	// Everything else...
	return INVALID;
}


/*
=============================================
helpText
Function to output default application text
=============================================
*/
void CLI::helpText()
{
	std::cout << USAGE << std::endl
		<< "\r\n"
		<< CLI_HELP << std::endl
		<< CLI_VERSION << std::endl
		<< "\r\n"
		<< RLFILE_OPEN << std::endl
		<< "\r\n"
		<< std::endl;
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

//
// Temporary junk
//
/*
for (int n = 0; n < argc; n++)
{
std::cout << std::string(argv[n]) << std::endl;
// TODO
// concat:  for each , += string to concat
}
*/