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
	std::vector<char> test = ReadAllBytes(filename);

	size_t fileSize = test.size();
	/*
	std::ifstream rl(filename);

	rl.seekg(0, std::ios::end);
	size_t fileSize = rl.tellg();

	char *buffer = new char[fileSize];

	rl.seekg(0, std::ios::beg);
	rl.read(buffer, fileSize);

	rl.close();
	*/

	std::cout << "\tFile: " << filename << std::endl;
	std::cout << "\tSize: " << fileSize << " bytes" << std::endl;

	std::cout << "\n\t[CONTENTS]\n" << std::endl;

	int blockSize = 20;
	int byte = 0;

	for (int i = 0; i < fileSize / blockSize; ++i) {
		char name[12];

		for (int j = 0; j < blockSize; ++j) {
			// [0] to [12] characters that represent *.GJD filename

			if (j < 12) {
				//name[j] = buffer[byte];

				name[j] = test[byte];
			}
			else {
				if (j < 16) {
					//std::cout << arr << std::endl;
				}
			}

			byte++;
		}

		std::cout << "\t" << name << std::endl;
		std::cout << "\t" << "\tOffset: " << std::endl;
		std::cout << "\t" << "\tSize: " << std::endl;
	}
}