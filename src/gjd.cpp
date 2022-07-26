// gjd.cpp

#include <Windows.h>
#include <string>
#include <fstream>

#include "gjd.h"
#include "rl.h"

#include "xmi.h"

void openGJDFile(std::string filename, GJDFileInfo* gjdFileList)
{
	std::ifstream gjdFile;
	gjdFile.open(filename, std::ios::binary);
	if (gjdFile.is_open())
	{
		/*
		
		OK so it's looking like you should do a for loop
		i = 0,
		i is less than whatever the last enum is
		
		This is totally a perfect solution since this can't be 
		dynamic to begin with, working  with enums is a good idea.
		
		Add a 3rd paramenter to this function
		the last enum of WHATEVER.RL needs to be passed in,
		as the length so this function can be as dynamic as possible
		
		Return type should be - an array of char bytestreams?
		
		*/
	}
	else {
		std::string error = filename + " could not be opened.";

		MessageBox(
			NULL,
			error.c_str(),
			"t7gtools",
			MB_ICONERROR
		);
	}
}