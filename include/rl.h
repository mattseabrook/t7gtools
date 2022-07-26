// rl.h

#ifndef RL_H
#define RL_H

#include <string>

//===========================================================================

struct GJDFileInfo {
	std::string filename;
	uint32_t offset;
	uint32_t length;
};

//===========================================================================

GJDFileInfo* openRLFile(std::string filename);

//===========================================================================

#endif