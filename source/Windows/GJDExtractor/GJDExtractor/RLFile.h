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
	static void open(std::string filename);
	static void procBlock(std::vector<char> data, std::string filename);
};

//-------------------


#endif // __RLFILE_H