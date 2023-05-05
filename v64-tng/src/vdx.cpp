#include <vector>
#include <stdexcept>

#include "vdx.h"
#include "lzss.h"
#include "bitmap.h"

std::vector<uint8_t> parseVDX(const std::vector<uint8_t> &buffer)
{
    // Initialize a vector store the VDX header
    VDXHeader header;

    header.identifier = buffer[0] | (buffer[1] << 8);
    header.unknown.assign(buffer.begin() + 2, buffer.begin() + 8);

    // Skip the VDX Header
    size_t offset = 8; // Changed the type of 'offset' to 'size_t'

    // Initialize a vector to store the VDX chunks
    std::vector<VDXChunk> chunks;

    // Initialize a vector to store the output data
    std::vector<uint8_t> VDXData;

    // Iterate through each chunk in the buffer
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

        std::vector<uint8_t> decompressedData;

        // Handle different chunk types based on the chunkType value
        switch (chunk.chunkType)
        {
        case 0x00:
            // Handle chunk type 0x00
            break;
        case 0x20:
            // Handle chunk type 0x20
            decompressedData = lzssDecompress(chunk.data, chunk.lengthMask, chunk.lengthBits);
            VDXData = processType20Chunk(decompressedData);
            break;
        case 0x80:
            // Handle chunk type 0x80
            break;
        default:
            // Handle unknown chunk types
            break;
        }

        // Add the parsed chunk to the vector of chunks
        chunks.push_back(chunk);
    }

    return VDXData;
}