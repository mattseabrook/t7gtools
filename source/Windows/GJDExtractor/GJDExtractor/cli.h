// cli.h
#ifndef CLI_H
#define CLI_H

#define EXE_NAME "t7gtools"
#define VER_NUM "0.1 alpha"

/*
=============================================================================
CLI Interface
=============================================================================
*/

class CLI
{
public:
	void helpText();
	void verInfo();
};

/*
=============================================================================
Options
Enumerate user
=============================================================================
*/

enum Options
{
	RLFILE,
	GJDFILE,
	HELP,
	VERSION,
	INVALID
};

Options switchProc(std::string Q);

//
// CLI text definitions
//

#define USAGE "Usage: " EXE_NAME " -[option] , --[option]"

#define CLI_VERSION "\t-v , --version\t\tShow information about this tool."
#define CLI_HELP "\t-h , --help\t\tDisplay extended help information."
#define RLFILE_OPEN "\t-r , --rlfile\t\tOpen *.RL file and extract it's contents (*.VDX)"

//-------------------

#endif // __CLI_H