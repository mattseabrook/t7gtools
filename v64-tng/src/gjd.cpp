#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <algorithm>
#include <filesystem>

#include "rl.h"
#include "vdx.h"

void parseGJDFile(const std::string &rlFilename)
{
    std::vector<RLEntry> rlEntries = parseRLFile(rlFilename);

    std::string gjdFilename = rlFilename.substr(0, rlFilename.size() - 3) + ".GJD";

    std::ifstream gjdFile(gjdFilename, std::ios::binary);

    if (!gjdFile)
    {
        std::cerr << "Error opening GJD file: " << gjdFilename << std::endl;
        return;
    }

    for (const auto &entry : rlEntries)
    {
        size_t offset = entry.offset;
        size_t length = entry.length;

        // Read the VDX data from the GJD file
        std::vector<uint8_t> vdxData(length);
        gjdFile.seekg(offset, std::ios::beg);
        gjdFile.read(reinterpret_cast<char *>(vdxData.data()), length);

        // Process the VDX data and store it in a VDXFile object
        VDXFile vdxFile = parseVDXFile(entry.filename, vdxData);

        // DEBUG-Write the VDX data to a file inside the sub-directory named dirName
        std::string dirName = rlFilename;
        std::replace(dirName.begin(), dirName.end(), '.', '_');
        std::ofstream vdxFileOutput(dirName + "/" + entry.filename, std::ios::binary);
        vdxFileOutput.write(reinterpret_cast<char *>(vdxData.data()), length);
    }
}
