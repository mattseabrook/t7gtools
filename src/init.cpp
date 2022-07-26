// init.cpp

/*

Here we are going to initialize the game as per the DOSBox Debugger data referenced in README.md

*/
#include "xmi.h"

int init() {
	if (!loadMusic())
		return -1;
	
}