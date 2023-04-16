// lzss.h

#ifndef LZSS_H
#define LZSS_H

#include <vector>

//===========================================================================

std::vector<uint8_t> decompressBlock(const std::vector<uint8_t> &compressedBytes, uint8_t lengthBits, uint32_t blockSize);

//===========================================================================

#endif