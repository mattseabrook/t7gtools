// rl.h

#ifndef RL_H
#define RL_H

#include <string>

//===========================================================================

struct GJDFileInfo {
	std::string name;
	uint32_t offset;
	uint32_t size;
};

//===========================================================================

GJDFileInfo* openRLFile(std::string filename);

//===========================================================================

#endif