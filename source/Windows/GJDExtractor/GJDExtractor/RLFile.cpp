// RLFile.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils.h"
#include "RLFile.h"
#include "GJDFile.h"

// *.RL Bytestream
std::vector<char> rlData;

/*
=============================================
RLFile::open

Open the *.RL file and break it into chunks
based on RL_BLOCKSIZE
=============================================
*/
void RLFile::open(std::string filename)
{
	// Input validation to prevent opening of any other file type

	std::string gjdFile = filename.substr(0, filename.size() - 2);
	std::string newExt = "GJD";

	gjdFile.append(newExt);

	std::cout << "*.RL file: " + filename << std::endl;
	std::cout << "*.GJD file: " + gjdFile << std::endl;

	gjdData = Utils::ReadAllBytes(gjdFile);
	
	rlData = Utils::ReadAllBytes(filename);

	size_t fileSize = rlData.size();
	int blockSize = RL_BLOCKSIZE;
	size_t blocks = fileSize / blockSize;
	int byte = 0;

	for (int i = 1; i < blocks; i++) {
		int end = i * blockSize;
		int start = end - blockSize;

		std::vector<char>::const_iterator first = rlData.begin() + start;
		std::vector<char>::const_iterator last = rlData.begin() + end;
		std::vector<char> block(first, last);

		procBlock(block, filename);
	}
}


/*
=============================================
RLFile::procBlock

Process *.RL data chunks, based on RL_BLOCKSIZE
=============================================
*/
void RLFile::procBlock(std::vector<char> data, std::string filename)
{
	//
	// File Name
	//
	char name[RL_NAME];

	for (int i = 0; i < RL_NAME - 1; i++) {
		name[i] = data[i];
	}

	//
	// GJD Offset
	//
	uint8_t gjdOffset[RL_OFFSET] = { data[12],
									 data[13],
									 data[14],
									 data[15] };

	uint32_t offset = Utils::read_u32_le(gjdOffset);

	//
	// VDX File size
	//
	uint8_t vdxFileSize[RL_SIZE] = { data[16],
									 data[17],
									 data[18],
									 data[19] };

	uint32_t filesize = Utils::read_u32_le(vdxFileSize);

	// Call to break apart GJD file
	GJDFile::vdxRipper(filename, name, offset, filesize);
}