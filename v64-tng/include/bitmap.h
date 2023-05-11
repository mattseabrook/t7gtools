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

struct RGBColor {
    uint8_t r, g, b;
};

template <typename T>
T readLittleEndian(const uint8_t *data) {
    T result = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        result |= static_cast<T>(data[i]) << (i * 8);
    }
    return result;
}

void savePNG(const std::string &filename, const std::vector<uint8_t> &imageData, int width, int height);
std::vector<uint8_t> getBitmapData(const std::vector<uint8_t> &chunkData);
void expandColorMap(uint8_t *out, uint16_t colorMap, uint8_t color1, uint8_t color0);
void decodeBlockStill(std::vector<uint8_t> &outputImageData, uint8_t *colors, uint16_t imageWidth, int tileX, int tileY, const std::vector<RGBColor> &palette);

#endif // BITMAP_H