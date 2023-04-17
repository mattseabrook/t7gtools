// gjd.cpp

#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>

#include "gjd.h"
#include "rl.h"
#include "xmi.h"

char** openGJDFile(std::string filename, GJDFileInfo* gjdFiles, int entries)
{
	std::ifstream gjdFile;
	gjdFile.open(filename, std::ios::binary);
	if (gjdFile.is_open())
	{
		char** gjdFileData = new char* [entries];

		for (int i = 0; i < entries; i++)
		{
			gjdFileData[i] = new char[gjdFiles[i].size];
			
			gjdFile.seekg(gjdFiles[i].offset, std::ios::beg);
			gjdFile.read(gjdFileData[i], gjdFiles[i].size);
		}

		return gjdFileData;
	}
	else {
		std::string error = filename + " could not be opened.";

		MessageBox(
			NULL,
			error.c_str(),
			"t7gtools",
			MB_ICONERROR
		);

		exit(1);
	}
}