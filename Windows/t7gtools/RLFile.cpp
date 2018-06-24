// RLFile.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

#include "utils.h"
#include "RLFile.h"
#include "GJDFile.h"

// *.RL Bytestream
std::vector<char> rlData;

// *.GJD working directory
std::string GJDFile::gjdDir;

/*
=============================================
RLFile::open

Open the *.RL file and break it into chunks
based on RL_BLOCKSIZE
=============================================
*/
void RLFile::open(std::string filename)
{
	// TODO
	// Input validation to prevent opening of any other file type

	GJDFile::gjdDir = filename.substr(0, filename.size() - 3);

	if (CreateDirectory(GJDFile::gjdDir.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError()) {
	}

	std::string gjdFile = GJDFile::gjdDir + ".GJD";

	// Load *.GJD file into memory
	gjdData = Utils::ReadAllBytes(gjdFile);

	// Load *.RL file into memory
	rlData = Utils::ReadAllBytes(filename);

	size_t fileSize = rlData.size();
	int blockSize = RL_BLOCKSIZE;
	size_t blocks = fileSize / blockSize + 1;
	int byte = 0;

	for (int i = 1; i < blocks; i++) {
		int end = i * blockSize;
		int start = end - blockSize;

		std::vector<char>::const_iterator first = rlData.begin() + start;
		std::vector<char>::const_iterator last = rlData.begin() + end;
		std::vector<char> block(first, last);

		procBlock(block);

		// Free memory
		if (i == blocks - 1) {
			std::vector<char>().swap(block);
		}
	}
}


/*
=============================================
RLFile::procBlock

Process *.RL data chunks, based on RL_BLOCKSIZE
=============================================
*/
void RLFile::procBlock(std::vector<char> &data)
{
	//
	// File Name
	//
	char name[RL_NAME];

	for (int i = 0; i < RL_NAME; i++) {
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
	GJDFile::vdxRipper(name, offset, filesize);
}