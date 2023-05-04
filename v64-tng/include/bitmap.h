// bitmap.h

#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include <cstdint>
#include <string>

/*
===============================================================================

    7th Guest - Bitmap

    This header file contains the function prototype for saving a bitmap

===============================================================================
*/

void savePNG(const std::string &filename, const std::vector<uint8_t> &imageData, int width, int height);
std::vector<uint8_t> processType20Chunk(const std::vector<uint8_t> &chunkData);

#endif // BITMAP_H