// RLFile.h
#ifndef RLFILE_H
#define RLFILE_H

#include <vector>

//-------------------


/*
=============================================================================
Rob Landeros (RL) fileType definitions
=============================================================================
*/
#define RL_BLOCKSIZE		20
#define RL_NAME				12
#define RL_OFFSET			4
#define RL_SIZE				4


//-------------------


/*
=============================================================================
RLFile Class
=============================================================================
*/
class RLFile
{
public:
	void open(const char* filename);
	std::vector<char> split(std::vector<char> rlBlock);
};

//-------------------


#endif // __RLFILE_H