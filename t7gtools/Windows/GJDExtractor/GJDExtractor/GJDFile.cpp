// GJDFile.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "utils.h"
#include "GJDFile.h"

// *.GJD Bytestream
std::vector<char> gjdData;

void GJDFile::vdxRipper(char * name, uint32_t &offset, uint32_t &filesize)
{
	std::string pathname = GJDFile::gjdDir + "\\" + name;

	int a, b, end;
	a = int(offset);
	b = int(filesize);

	// Testing...
	std::cout << name << "-" << a << "-" << b << " - Writing to: \\" << pathname << std::endl;

	if (a == 0) {
		end = b - 1;
	}
	else {
		end = a + b;
	}

	std::vector<char>::const_iterator first = gjdData.begin() + a;		// OFFSET
	std::vector<char>::const_iterator last = gjdData.begin() + end;		// OFFSET + FILESIZE
	std::vector<char> block(first, last);								// *.VDX data chunk / byte stream;

	std::ofstream textout(pathname.c_str(), std::ios::out | std::ios::binary);
	textout.write((const char*)&block[0], block.size());
	textout.close();

	// Cleanup
	std::vector<char>().swap(block);
}