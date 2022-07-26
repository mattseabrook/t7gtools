// rl.cpp

#include <Windows.h>
#include <string>
#include <fstream>

#include "rl.h"

GJDFileInfo* openRLFile(std::string filename)
{
#ifdef _DEBUG
	std::string rlStringData;
#endif

	std::ifstream rlFile;
	rlFile.open(filename, std::ios::binary);
	if (rlFile.is_open())
	{
		rlFile.seekg(0, std::ios::end);
		const int fileSize = rlFile.tellg();									// Size of the *.RL file in bytes
		rlFile.seekg(0, std::ios::beg);

		GJDFileInfo* array = new GJDFileInfo[fileSize / 20];			// Dynamic array of VDXFileInfo structs
		int i = 0;														// Counter for the array

		char buffer[20]{};												// Buffer that holds 20 bytes
		char c;															// single character byte $xx
		int n = 0;														// counter for buffer

		while (rlFile.get(c))
		{
			// push c into buffer
			buffer[n] = c;

			// check if buffer is full
			if (n == 19)
			{
				array[i].filename = std::string(buffer, 0, 12);			// $00 - $11 : Filename
				array[i].offset = *(uint32_t*)(buffer + 12);			// $12 - $15 : Offset
				array[i].length = *(uint32_t*)(buffer + 16);			// $16 - $19 : Length

#ifdef _DEBUG
				rlStringData += array[i].filename +
					"," +
					std::to_string(array[i].offset) +
					"," +
					std::to_string(array[i].length) +
					"\n";
#endif

				// Empty the buffer
				for (int j = 0; j < 20; j++)
				{
					buffer[j] = '\0';
				}

				n = 0;

				i++;
			}
			else {
				n++;
			}
		}

#ifdef _DEBUG
		if ((strcmp(__argv[1], "-R") == 0 || strcmp(__argv[1], "-rl") == 0))
		{
			MessageBox(NULL, rlStringData.c_str(), "RL File", MB_OK);

			std::ofstream rlDataFile;
			rlDataFile.open("rlData.txt", std::ios::binary);
			rlDataFile << rlStringData;
			rlDataFile.close();
		}
#endif

		rlFile.close();

		// Return array
		return array;
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

		// Exit w/error
		exit(1);
	}
}