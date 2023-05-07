// vdx.cpp

#include <vector>
#include <stdexcept>

#include "vdx.h"
#include "lzss.h"
#include "bitmap.h"

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

void parseVDXChunks(VDXFile &vdxFile)
{
    for (VDXChunk &chunk : vdxFile.chunks)
    {
        std::vector<uint8_t> unprocessedData;

        switch (chunk.chunkType)
        {
        case 0x00:
            // Handle chunk type 0x00
            break;
        case 0x20:
            // Handle chunk type 0x20
            unprocessedData = lzssDecompress(chunk.data, chunk.lengthMask, chunk.lengthBits);
            chunk.data = processType20Chunk(unprocessedData);
            break;
        case 0x80:
            // Handle chunk type 0x80
            break;
        default:
            // Handle unknown chunk types
            break;
        }
    }
}