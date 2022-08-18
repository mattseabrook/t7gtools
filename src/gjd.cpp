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
#ifdef _DEBUG
	std::string test;
#endif		
	
	std::ifstream gjdFile;
	gjdFile.open(filename, std::ios::binary);
	if (gjdFile.is_open())
	{
		char** gjdFileData = new char* [entries];

		for (int i = 0; i < entries; i++)
		{
#ifdef _DEBUG			
			test += gjdFiles[i].name + " - ";
#endif	
			gjdFileData[i] = new char[gjdFiles[i].size];
			
			gjdFile.seekg(gjdFiles[i].offset, std::ios::beg);
			gjdFile.read(gjdFileData[i], gjdFiles[i].size);
		}

#ifdef _DEBUG
		MessageBox(NULL, test.c_str(), "GJD.CPP - Names", MB_OK);
		std::stringstream ss;
		ss << entries;
		std::string s = ss.str();
		MessageBox(NULL, s.c_str(), "GJD.CPP - Count", MB_OK);

		std::string folderName = filename.substr(0, filename.find_last_of('.'));
		CreateDirectory(folderName.c_str(), NULL);
		
#endif	
		
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