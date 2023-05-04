// gjd.h

#ifndef GJD_H
#define GJD_H

#include <string>

#include "rl.h"

/*
===============================================================================

    7th Guest - GJD Parser

    This header file contains the function prototype for parsing a GJD file
    to get the VDX file data.

===============================================================================
*/

// Function prototype for parseGJDFile
void parseGJDFile(const std::string &gjdFilename, const std::string &rlFilename);

#endif // GJD_H