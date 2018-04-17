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
	size_t blocks = fileSize / blockSize;
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
	//
	// File Name
	//
	char name[RL_NAME];

	for (int i = 0; i < RL_NAME - 1; i++) {
		name[i] = data[i];
	}

	std::cout << "filename: " << name << std::endl;

	//
	// GJD Offset
	//
	uint8_t gjdOffset[RL_OFFSET] = { data[12],
									 data[13],
									 data[14],
									 data[15] };

	uint32_t offset = read_u32_le(gjdOffset);

	std::cout << "Offset: " << offset << std::endl;

	//
	// VDX File size
	//
	uint8_t vdxFileSize[RL_SIZE] = { data[16],
									 data[17],
									 data[18],
									 data[19] };

	uint32_t filesize = read_u32_le(vdxFileSize);

	std::cout << "File size: " << filesize << std::endl;

	// Call to break apart GJD file
	//GJDFile::vdxRip(name, offset, filesize);
}