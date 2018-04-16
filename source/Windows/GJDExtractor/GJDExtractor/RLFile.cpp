// RLFile.cpp

#include <iostream>
#include <fstream>
#include <vector>

#include "RLFile.h"
#include "utils.h"


/*
=============================================
RLFile::open

Open the *.RL file and break it into chunks
based on RL_BLOCKSIZE
=============================================
*/
void RLFile::open(const char* filename)
{
	std::vector<char> rl = ReadAllBytes(filename);

	size_t fileSize = rl.size();
	int blockSize = RL_BLOCKSIZE;
	int blocks = fileSize / blockSize;
	int byte = 0;

	std::cout << "\tFile: " << filename << std::endl;
	std::cout << "\tSize: " << fileSize << " bytes" << std::endl;
	std::cout << "\tBlocks: " << blocks << std::endl;

	std::cout << "\n\t[CONTENTS]\n" << std::endl;

	for (int i = 1; i < blocks; i++) {
		int end = i * blockSize;
		int start = end - blockSize;

		std::cout << "\n\nBLOCK # " << i << std::endl;
		std::cout << "Start byte: " << start << std::endl;
		std::cout << "End byte: " << end << std::endl;

		//... view range of vector
		std::vector<char>::const_iterator first = rl.begin() + start;
		std::vector<char>::const_iterator last = rl.begin() + end;
		std::vector<char> newVec(first, last);

		std::cout << '\n';

		int len = newVec.size();

		for (int j = 0; j < len; j++) {
			std::cout << newVec[j];
		}
	}


	//...
	// i * blocksize


	//std::cout << "New vector size: " << test.size();

	// Next time try:
	// Make a local array or vector, store the 20 blocks in it.
	// try hard coding [0:12] [13:16] [17:20]

	/*

	//It's an O(N) operation to construct the new vector, but there isn't really a better way.
	std::vector<T>::const_iterator first = myVec.begin() + 100000;
	std::vector<T>::const_iterator last = myVec.begin() + 101000;
	std::vector<T> newVec(first, last);

	*/


	/*
	for (int i = 0; i < fileSize / blockSize; ++i) {
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
	*/
}