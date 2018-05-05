// GJDFile.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils.h"
#include "GJDFile.h"

void GJDFile::vdxRipper(std::string filename, char * name, uint32_t offset, uint32_t filesize)
{
	filename = filename.substr(0, filename.size() - 2);
	std::string newExt = "GJD";

	filename.append(newExt);

	std::cout << filename << std::endl;

	std::vector<char> gjd = Utils::ReadAllBytes(filename);

	// for i < filesize
	// stream vector
}