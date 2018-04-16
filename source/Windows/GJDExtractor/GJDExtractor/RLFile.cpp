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

	for (int i = 1; i < blocks; i++) {
		int end = i * blockSize;
		int start = end - blockSize;

		std::vector<char>::const_iterator first = rl.begin() + start;
		std::vector<char>::const_iterator last = rl.begin() + end;
		std::vector<char> block(first, last);

		procBlock(block);
	}
}


/*
=============================================
RLFile::procBlock

Process *.RL data chunks, based on RL_BLOCKSIZE
=============================================
*/
void RLFile::procBlock(std::vector<char> data)
{
	int i;

	//
	// File Name
	//
	char name[RL_NAME];

	for (i = 0; i < RL_NAME - 1; i++) {
		name[i] = data[i];
	}

	std::cout << "filename: " << name << std::endl;

	//
	// GJD Offset
	//
	uint32_t gjdOffset;

	for (i = 11; i < RL_OFFSET - 1; i++) {
		//name[i] = data[i];
		std::cout << i;
	}

	//std::cout << "filename: " << name << std::endl;


	// Raw
	int len = data.size();
	for (int j = 0; j < len; j++) {
		std::cout << data[j];
	}

	std::cout << '\n';
}