#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "rl.h"
#include "vdx.h"

void parseGJDFile(const std::string &gjdFilename, const std::string &rlFilename)
{
    std::vector<VDXEntry> vdxEntries = parseRLFile(rlFilename);

    std::ifstream gjdFile(gjdFilename, std::ios::binary);

    if (!gjdFile)
    {
        std::cerr << "Error opening GJD file: " << gjdFilename << std::endl;
        return;
    }

    for (const auto &entry : vdxEntries)
    {
        size_t offset = entry.offset;
        size_t length = entry.length;

        // Read the VDX data from the GJD file
        std::vector<uint8_t> vdxData(length);
        gjdFile.seekg(offset, std::ios::beg);
        gjdFile.read(reinterpret_cast<char *>(vdxData.data()), length);

        // Process the VDX data
        parseVDX(vdxData);
    }
}
