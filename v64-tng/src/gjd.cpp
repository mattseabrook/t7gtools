#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "rl.h"
#include "gjd.h"
#include "vdx.h"

/*
===============================================================================
Function Name: parseGJDFile

Description:
    - TBD

Parameters:
    - rlFilename: the 7th Guest RL file to parse

Return:
    - TBD

Notes:
    - None.
===============================================================================
*/
std::vector<VDXFile> parseGJDFile(const std::string &rlFilename)
{
    std::vector<RLEntry> rlEntries = parseRLFile(rlFilename);

    std::string gjdFilename = rlFilename.substr(0, rlFilename.size() - 3) + ".GJD";

    std::ifstream gjdFile(gjdFilename, std::ios::binary | std::ios::ate);

    if (!gjdFile)
    {
        std::cerr << "Error opening GJD file: " << gjdFilename << std::endl;
        return std::vector<VDXFile>{}; // Return an empty result
    }

    std::vector<VDXFile> GJDData;

    size_t entryIndex = 0;
    for (const auto &entry : rlEntries)
    {
        std::cout << entry.filename << " | " << entry.offset << " | " << entry.length << std::endl;
        
        size_t offset = entry.offset;
        size_t length = entry.length;

        // Read the VDX data from the GJD file
        std::vector<uint8_t> vdxData(length);
        gjdFile.seekg(offset, std::ios::beg);
        gjdFile.read(reinterpret_cast<char *>(vdxData.data()), length);

        if (!gjdFile)
        {
            std::cerr << "Error reading VDX data from GJD file: " << gjdFilename << std::endl;
            gjdFile.clear(); // Clear the error state
            entryIndex++;
            continue;
        }

        // Process the VDX data and store it in a VDXFile object
        VDXFile vdxFile = parseVDXFile(entry.filename, vdxData);

        // Add the VDXFile object to the result
        GJDData.push_back(vdxFile);

        entryIndex++;
    }

    return GJDData;
}