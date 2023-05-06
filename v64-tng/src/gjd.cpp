#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// remove after debugging
#include <algorithm>

#include "rl.h"
#include "vdx.h"

void parseGJDFile(const std::string &rlFilename)
{
    std::vector<VDXEntry> vdxEntries = parseRLFile(rlFilename);

    std::string gjdFilename = rlFilename.substr(0, rlFilename.size() - 3) + ".GJD";
    
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
        // parseVDX(vdxData);
        std::string dirName = rlFilename;
        std::replace(dirName.begin(), dirName.end(), '.', '_');

        // write entry to a file inside the sub-directory named dirName. the file name is entry.filename:
        std::ofstream vdxFile(dirName + "/" + entry.filename, std::ios::binary);
        vdxFile.write(reinterpret_cast<char *>(vdxData.data()), length);
    }
}
