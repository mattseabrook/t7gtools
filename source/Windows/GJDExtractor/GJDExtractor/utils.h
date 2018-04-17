// utils.h

#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <vector>
//-------------------


/*
=============================================
ReadAllBytes(filename)

Stream the binary data to a vector,
and return that vector.
=============================================
*/
static std::vector<char> ReadAllBytes(char const* filename)
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
uint32_t read_u32_le(uint8_t* bytes)
{
	uint32_t value;
	value = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
	return value;
}


//-------------------

#endif // __UTILS_H