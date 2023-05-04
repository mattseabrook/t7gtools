// vdx.h

#ifndef VDX_H
#define VDX_H

#include <cstdint>
#include <vector>

/*
===============================================================================

    7th Guest - VDX Parser

    This header file contains the structs and function prototypes for parsing
    VDX headers and chunks.

===============================================================================
*/

// VDXHeader struct
struct VDXHeader
{
    uint16_t identifier;
    std::vector<uint8_t> unknown;
};

// VDXChunk struct
struct VDXChunk
{
    uint8_t chunkType;
    uint32_t dataSize;
    uint8_t lengthMask;
    uint8_t lengthBits;
    std::vector<uint8_t> data;
};

// VDXFile struct
struct VDXFile
{
    VDXHeader header;
    std::vector<VDXChunk> chunks;
};

std::vector<uint8_t> parseVDX(const std::vector<uint8_t> &buffer);

#endif // VDX_H