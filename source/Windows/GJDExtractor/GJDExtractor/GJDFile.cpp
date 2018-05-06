// GJDFile.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils.h"
#include "GJDFile.h"

// *.GJD Bytestream
std::vector<char> gjdData;

void GJDFile::vdxRipper(std::string filename, char * name, uint32_t offset, uint32_t filesize)
{
	// for i < filesize
	// stream vector

	std::cout << name << "-" << offset << "-" << filesize << std::endl;
}