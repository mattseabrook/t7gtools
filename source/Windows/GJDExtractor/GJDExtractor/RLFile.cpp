// RLFile.cpp

#include <iostream>
#include <fstream>
#include <vector>

#include "RLFile.h"

static std::vector<char> ReadAllBytes(char const* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}


void RLFile::open(const char* filename)
{
	std::vector<char> rl = ReadAllBytes(filename);

	size_t fileSize = rl.size();

	std::cout << "\tFile: " << filename << std::endl;
	std::cout << "\tSize: " << fileSize << " bytes" << std::endl;

	std::cout << "\n\t[CONTENTS]\n" << std::endl;

	int blockSize = 20;
	int byte = 0;

	for (int i = 0; i < fileSize / blockSize; ++i) {

		// Next time try:
		// Make a local array or vector, store the 20 blocks in it.
		// try hard coding [0:12] [13:16] [17:20]

		char name[12];
		uint32_t offset[4];
		int offset_counter = 0;
		uint32_t size[4];
		int size_counter = 0;

		for (int j = 0; j < blockSize; ++j) {
			if (j < 12) {
				name[j] = rl[byte];
			}
			else if (j < 16) {
				offset[offset_counter] = rl[byte];
				offset_counter++;
			}
			else if (j < blockSize) {
				size[size_counter] = rl[byte];
				size_counter++;
			}

			byte++;
		}

		std::cout << "\t" << name << std::endl;
		int a = int(offset);
		std::cout << "\t" << "\tOffset: " << a << std::endl;
		std::cout << "\t" << "\tSize: " << size << std::endl;
	}
}