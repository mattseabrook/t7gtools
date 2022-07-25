// rl.cpp

#include <Windows.h>
#include <string>
#include <fstream>

#include "rl.h"

void openRLFile(std::string filename)
{
#ifdef _DEBUG
	std::string rlData;
#endif

	std::ifstream rlFile;
	rlFile.open(filename, std::ios::binary);
	if (rlFile.is_open())
	{
		struct {
			std::string filename;
			uint32_t offset;
			uint32_t length;
		} VDXFileInfo;

		char buffer[20]{};												// Buffer that holds 20 bytes
		char c;															// single character byte $xx
		int i = 0;														// counter for buffer

		while (rlFile.get(c))
		{
			// push c into buffer
			buffer[i] = c;

			// check if buffer is full
			if (i == 19)
			{
				VDXFileInfo.filename = std::string(buffer, 0, 12);		// $00 - $11 : Filename
				VDXFileInfo.offset = *(uint32_t*)(buffer + 12);			// $12 - $15 : Offset
				VDXFileInfo.length = *(uint32_t*)(buffer + 16);			// $16 - $19 : Length

#ifdef _DEBUG
				rlData += VDXFileInfo.filename +
					"," +
					std::to_string(VDXFileInfo.offset) +
					"," +
					std::to_string(VDXFileInfo.length) +
					"\n";
#endif

				// Empty the buffer
				for (int j = 0; j < 20; j++)
				{
					buffer[j] = '\0';
				}
				i = 0;
			}
			else {
				i++;
			}
		}

#ifdef _DEBUG
		MessageBox(NULL, rlData.c_str(), "RL File", MB_OK);

		std::ofstream rlDataFile;
		rlDataFile.open("rlData.txt", std::ios::binary);
		rlDataFile << rlData;
		rlDataFile.close();
#endif

		rlFile.close();
	}
	else
	{
		MessageBox(
			NULL,
			"Invalid command-line arguments provided!\n\n\
Usage:\n\n\
t7gtools.exe [-R | -rl] filename.rl\n\
t7gtools.exe [-v | -version]\n\
t7gtools.exe [-d | -demo]",
"t7gtools",
MB_ICONERROR
);
	}
}