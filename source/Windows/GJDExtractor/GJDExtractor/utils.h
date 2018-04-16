// RLFile.h
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
print

Log bytes to the consle
=============================================
*/
template<typename T>
void print(std::vector<T> const &v)
{
	for (auto &i : v)
		std::cout << i << ' ';

	std::cout << '\n';
}


//-------------------


#endif // __UTILS_H