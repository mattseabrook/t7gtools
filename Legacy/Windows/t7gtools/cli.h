// cli.h
#ifndef CLI_H
#define CLI_H

const char EXE_NAME[] = "t7gtools";
const char VER_NUM[] = "0.1 alpha";

/*
=============================================================================
CLI Interface
=============================================================================
*/

class CLI
{
public:
	static void tagLine();
	static void verInfo();
};

/*
=============================================================================
Options
Enumerate user-supplied CLI arguments
=============================================================================
*/

enum Options
{
	RLFILE,
	GJDFILE,
	HELP,
	VERSION,
	TEST,
	INVALID
};

Options switchProc(std::string Q);

//
// CLI text definitions
//

const char USAGE[] = "Usage: EXE_NAME -[option] , --[option]\r\n\r\n"
"\t-v , --version\t\tShow information about this tool.\r\n"
"\t-h , --help\t\tDisplay extended help information.\r\n"
"\t-r , --rlfile\t\tOpen *.RL file and extract it's contents (*.VDX)";

//-------------------

#endif // __CLI_H