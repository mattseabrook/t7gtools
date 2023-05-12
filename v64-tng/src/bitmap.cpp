// bitmap.cpp

#include <vector>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <iostream>

#include <png.h>

#include "bitmap.h"

/*
===============================================================================
Function Name: savePNG

Description:
    - Saves a *.PNG file from the given image data.

Parameters:
    - filename: The filename of the PNG file to be wrteen.
    - imageData: x.
    - width: width of the image
    - height: height of the image

Return:
    - TBD

Notes:
    - imageData will be som.
===============================================================================
*/
void savePNG(const std::string &filename, const std::vector<uint8_t> &imageData, int width, int height)
{
    FILE *fp;
    errno_t err = fopen_s(&fp, filename.c_str(), "wb");
    if (err != 0 || !fp)
    {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr)
    {
        fclose(fp);
        throw std::runtime_error("Failed to create PNG write struct");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, nullptr);
        throw std::runtime_error("Failed to create PNG info struct");
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        throw std::runtime_error("Error during PNG initialization");
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    std::vector<png_bytep> row_pointers(height);
    for (int y = 0; y < height; ++y)
    {
        row_pointers[y] = const_cast<uint8_t *>(&imageData[y * width * 3]);
    }

    png_write_image(png_ptr, row_pointers.data());

    png_write_end(png_ptr, nullptr);

    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
}

// Convert LZSS decompressed data to a bitmap structure
std::vector<uint8_t> getBitmapData(const std::vector<uint8_t> &chunkData)
{
    // Parse the header
    uint16_t numXTiles = readLittleEndian<uint16_t>(chunkData.data());
    uint16_t numYTiles = readLittleEndian<uint16_t>(chunkData.data() + 2);
    uint16_t colourDepth = readLittleEndian<uint16_t>(chunkData.data() + 4);

    const int width = numXTiles * 4;
    const int height = numYTiles * 4;
    const int numPixels = width * height;

    const size_t headerSize = 6;    // 2 bytes for width, 2 bytes for height, and 2 bytes for color depth
    const size_t paletteSize = 768; // size of the palette in bytes for 8-bit color depth

    // Read the palette
    const uint8_t *paletteData = chunkData.data() + 6;

    // Modify the loop to iterate 256 times (for an 8-bit color depth)
    std::vector<RGBColor> palette;
    for (int i = 0; i < 256; ++i)
    {
        palette.push_back({paletteData[i * 3], paletteData[i * 3 + 1], paletteData[i * 3 + 2]});
    }

    const uint8_t *imageData = paletteData + (1 << colourDepth) * 3;

    const size_t imageDataSize = chunkData.size() - headerSize - paletteSize;
    const size_t expectedImageDataSize = numXTiles * numYTiles * 4; // each 4x4 tile is represented by 4 bytes

    // Process the decompressed image data according to the Type 0x20 chunk specifications
    std::vector<uint8_t> outputImageData(numPixels * 3);
    for (int tileY = 0; tileY < numYTiles; ++tileY)
    {
        for (int tileX = 0; tileX < numXTiles; ++tileX)
        {
            uint8_t colour1 = *imageData++;
            uint8_t colour0 = *imageData++;
            uint16_t colourMap = readLittleEndian<uint16_t>(imageData);
            imageData += 2;

            uint8_t colors[16];
            expandColorMap(colors, colourMap, colour1, colour0);
            decodeBlockStill(outputImageData, colors, width, tileX, tileY, palette);
        }
    }

    return outputImageData;
}

// This function is used to expand a 2-bit color map to a 4-bit color map
void expandColorMap(uint8_t *out, uint16_t colorMap, uint8_t color1, uint8_t color0)
{
    out += 16;
    for (int i = 16; i; i--)
    {
        uint8_t selector = -(colorMap & 1);
        *--out = (selector & color1) | (~selector & color0);
        colorMap >>= 1;
    }
}

// This function is used to decode a 4x4 block of pixels
void decodeBlockStill(std::vector<uint8_t> &outputImageData, uint8_t *colors, uint16_t imageWidth, int tileX, int tileY, const std::vector<RGBColor> &palette)
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            int globalX = tileX * 4 + x;
            int globalY = tileY * 4 + y;
            int pixelIndex = globalY * imageWidth + globalX;

            uint8_t color = colors[x + y * 4];
            RGBColor pixelColor = palette[color];
            outputImageData[pixelIndex * 3] = pixelColor.r;
            outputImageData[pixelIndex * 3 + 1] = pixelColor.g;
            outputImageData[pixelIndex * 3 + 2] = pixelColor.b;
        }
    }
}
