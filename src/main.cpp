// main.cpp

/*
	
	t7gtools

	Author: Matt Seabrook
	info@mattseabrook.net

*/
#include <Windows.h>

#include "cli.h"

//
// Main Entrypoint
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	INT nCmdShow)
{
	//
	// Process command-line arguments
	//
	if (__argc > 1)
	{
		proc_cli();
	}
	else
	{
		MessageBox(
			NULL, 
			"No command-line arguments/parameters were provided", 
			"Error", 
			MB_ICONERROR);
	}

	return 0;
}