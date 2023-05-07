// vdx.cpp

#include <vector>
#include <stdexcept>
#include <fstream>

#include "vdx.h"
#include "lzss.h"
#include "bitmap.h"

/*
===============================================================================
Function Name: parseVDXFile

Description:
    - Parses the VDX data and returns a VDXFile object containing the parsed data.

Parameters:
    - filename: The filename for the VDX data.
    - buffer: A vector containing the VDX data to be parsed.

Return:
    - A VDXFile object containing the parsed VDX data.

Notes:
    - None.
===============================================================================
*/
VDXFile parseVDXFile(const std::string &filename, const std::vector<uint8_t> &buffer)
{
    VDXFile vdxFile;
    vdxFile.filename = filename;

    vdxFile.identifier = buffer[0] | (buffer[1] << 8);
    std::copy(buffer.begin() + 2, buffer.begin() + 8, vdxFile.unknown.begin());

    size_t offset = 8;

    while (offset < buffer.size())
    {
        VDXChunk chunk;
        chunk.chunkType = buffer[offset];
        chunk.dataSize = buffer[offset + 1] | (buffer[offset + 2] << 8) | (buffer[offset + 3] << 16) | (buffer[offset + 4] << 24);
        chunk.lengthMask = buffer[offset + 5];
        chunk.lengthBits = buffer[offset + 6];
        offset += 7;
        chunk.data.assign(buffer.begin() + offset, buffer.begin() + offset + chunk.dataSize);
        offset += chunk.dataSize;

        vdxFile.chunks.push_back(chunk);
    }

    return vdxFile;
}

/*
===============================================================================
Function Name: parseVDXChunks

Description:
    - TBD

Parameters:
    - vdxFile: Fully populated VDXFile object.

Return:
    - TBD

Notes:
    - None.
===============================================================================
*/
void parseVDXChunks(VDXFile &vdxFile)
{
    for (VDXChunk &chunk : vdxFile.chunks)
    {
        std::string compressedFilename = vdxFile.filename + "-00-0x20-(compressed).bin";
        std::string decompressedFilename = vdxFile.filename + "-00-0x20-(decompressed).bin";

        std::ofstream ofsCompressed(compressedFilename, std::ios::binary);
        std::ofstream ofsDecompressed(decompressedFilename, std::ios::binary);

        std::vector<uint8_t> decompressedData;

        switch (chunk.chunkType)
        {
        case 0x00:
            // Handle chunk type 0x00
            break;
        case 0x20:
            // Handle chunk type 0x20
            decompressedData = lzssDecompress(chunk.data, chunk.lengthMask, chunk.lengthBits);

            ofsCompressed.write(reinterpret_cast<char *>(chunk.data.data()), chunk.data.size());
            ofsDecompressed.write(reinterpret_cast<char *>(decompressedData.data()), decompressedData.size());

            //chunk.data = processType20Chunk(decompressedData);
            break;
        case 0x80:
            // Handle chunk type 0x80
            break;
        default:
            // Handle unknown chunk types
            break;
        }

        ofsCompressed.close();
        ofsDecompressed.close();
    }
}