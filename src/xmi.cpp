// xmi.cpp

#include <Windows.h>

#include "rl.h"
#include "gjd.h"
#include "xmi.h"

bool loadMusic()
{
	GJDFileInfo* xmiFileList = openRLFile("xmi.rl");

	if (!xmiFileList)
		return false;
	
	char** xmiData = openGJDFile("xmi.gjd", xmiFileList, ini_sc);

	return true;
}