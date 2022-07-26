// cli.cpp

#include <Windows.h>

#include "gui.h"
#include "rl.h"

void proc_cli()
{
	if (strcmp(__argv[1], "-v") == 0 || strcmp(__argv[1], "-version") == 0)
	{
		MessageBox(
			NULL,
			"Author: Matt Seabrook\n\
info@mattseabrook.net\n\n\
EXPERIMENTAL",
"t7gtools",
MB_ICONINFORMATION
);
	}
	else if ((strcmp(__argv[1], "-d") == 0 || strcmp(__argv[1], "-demo") == 0))
	{
		openWindow();
	}
	else if ((strcmp(__argv[1], "-R") == 0 || strcmp(__argv[1], "-rl") == 0))
	{
		VDXFileInfo * rl_file_opened = openRLFile(__argv[2]);
	}
	else
	{
		MessageBox(
			NULL,
			"Invalid command-line arguments provided!\n\n\
Usage:\n\n\
t7gtools.exe [-v | -version]\n\
t7gtools.exe [-d | -demo]",
"t7gtools",
MB_ICONERROR
);
	}
}