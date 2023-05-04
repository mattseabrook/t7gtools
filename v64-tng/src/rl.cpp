// rl.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "rl.h"

//
// Parse RL file to get the VDX file locations
//
std::vector<VDXEntry> parseRLFile(const std::string &rlFilename)
{
    std::vector<VDXEntry> vdxEntries;

    std::ifstream rlFile(rlFilename, std::ios::binary);

    if (!rlFile)
    {
        std::cerr << "Error opening RL file: " << rlFilename << std::endl;
        return vdxEntries;
    }

    // Read the VDX file entries
    while (!rlFile.eof())
    {
        VDXEntry entry;
        char filename[13] = {0};
        rlFile.read(filename, 12);
        entry.filename.assign(filename);

        rlFile.read(reinterpret_cast<char *>(&entry.offset), sizeof(entry.offset));
        rlFile.read(reinterpret_cast<char *>(&entry.length), sizeof(entry.length));

        // Check if we reached the end of the file
        if (rlFile.eof()) break;

        vdxEntries.push_back(entry);
    }

    return vdxEntries;
}