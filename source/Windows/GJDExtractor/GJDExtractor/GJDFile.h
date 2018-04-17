// GJDFile.h
#ifndef GJDFILE_H
#define GJDFILE_H

#include <iostream>

class GJDFile
{
	static void vdxRipper(char * chunkName, uint32_t chunkOffset, uint32_t chunkSize);
};

#endif // __GJDFILE_H