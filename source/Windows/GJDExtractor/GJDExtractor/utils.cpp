// utils.cpp

#include <iostream>
#include <fstream>
#include <vector>

#include "utils.h"

/*
=============================================
ReadAllBytes(filename)

Stream the binary data to a vector,
and return that vector.
=============================================
*/
std::vector<char> Utils::ReadAllBytes(std::string filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}


/*
=============================================
read_u32_le

Return an unsigned 32-bit integer
in Little Endian
=============================================
*/
uint32_t Utils::read_u32_le(uint8_t* bytes)
{
	uint32_t value;
	value = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
	return value;
}