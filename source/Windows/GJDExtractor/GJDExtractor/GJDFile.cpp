// GJDFile.cpp

#include <iostream>
#include <fstream>
#include <vector>

#include "GJDFile.h"

void GJDFile::vdxRipper(char* filename, char * name, uint32_t offset, uint32_t filesize)
{
	//...
	filename[strlen(filename) - 3] = '\0';
	std::cout << filename << ".GJD";


	// for i < filesize
	// stream vector
}