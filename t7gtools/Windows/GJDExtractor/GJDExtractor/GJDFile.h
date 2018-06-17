// GJDFile.h
#ifndef GJDFILE_H
#define GJDFILE_H

#include <iostream>

//-------------------

extern std::vector<char> gjdData;

/*
=============================================================================
GJDFile Class
=============================================================================
*/
class GJDFile
{
public:
	static std::string gjdDir;
	static void vdxRipper(char * name, uint32_t &offset, uint32_t &filesize);
};

//-------------------

#endif // __GJDFILE_H