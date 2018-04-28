// GJDFile.cpp

#include <iostream>
#include <fstream>
#include <vector>

#include "utils.h"
#include "GJDFile.h"

void GJDFile::vdxRipper(char* filename, char * name, uint32_t offset, uint32_t filesize)
{
	filename[strlen(filename) - 3] = '\0';

	strcat_s(filename, ".GJD");
	std::cout << filename;

	std::vector<char> gjd = Utils::ReadAllBytes(filename);

	// for i < filesize
	// stream vector
}