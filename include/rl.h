// rl.h

#ifndef RL_H
#define RL_H

#include <string>

//===========================================================================

struct VDXFileInfo {
	std::string filename;
	uint32_t offset;
	uint32_t length;
};

//===========================================================================

VDXFileInfo* openRLFile(std::string filename);

//===========================================================================

#endif