// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

//-------------------

/*
=============================================================================
Utils Class
=============================================================================
*/
class Utils
{
public:
	static std::vector<char> ReadAllBytes(std::string filename);
	static uint32_t read_u32_le(uint8_t* bytes);
};

//-------------------

#endif // __UTILS_H