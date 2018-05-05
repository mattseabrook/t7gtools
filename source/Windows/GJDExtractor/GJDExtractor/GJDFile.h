// GJDFile.h
#ifndef GJDFILE_H
#define GJDFILE_H

#include <iostream>

class GJDFile
{
public:
	static void vdxRipper(std::string filename, char * name, uint32_t offset, uint32_t filesize);
};

#endif // __GJDFILE_H