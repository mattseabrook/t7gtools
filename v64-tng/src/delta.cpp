// delta.cpp

#include <vector>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <iostream>
#include <bitset>
#include <iomanip>

#include "bitmap.h"
#include "delta.h"

/*
===============================================================================
Function Name: getDeltaBitmapData

Description:
    - Convert LZSS Decompressed data to an 8-bit RGB raw bitmap data structure.
    This function takes a 0x25 chunk type (which contains delta bitmap data)
    and constructs a new complete image/frame from the delta bitmap data.

Parameters:
    - buffer: Decompressed chunk data
    - staticBitmap: The 0x20 static bitmap as 8-bit RGB raw bitmap data

Return:
    - std::vector<uint8_t>: 8-bit RGB raw bitmap data structure
===============================================================================
*/
std::vector<uint8_t> getDeltaBitmapData(std::vector<uint8_t> &buffer, std::vector<uint8_t> &staticBitmap)
{
    std::vector<uint8_t> deltaBitmapData = staticBitmap;

    // Reading 16-bit localPalSize
    uint16_t localPalSize = (static_cast<uint16_t>(buffer[0]) | (static_cast<uint16_t>(buffer[1]) << 8));

    size_t originalBufferSize = buffer.size();
    buffer.erase(buffer.begin(), buffer.begin() + 2); // Erase the processed bytes.

    // Check if there are local palette changes.
    if (localPalSize > 0)
    {
        std::bitset<16> palBitField[16];
        for (int i = 0; i < 16; ++i)
        {
            palBitField[i] = std::bitset<16>((static_cast<uint16_t>(buffer[0]) | (static_cast<uint16_t>(buffer[1]) << 8)));
            buffer.erase(buffer.begin(), buffer.begin() + 2); // Erase the processed bytes.
        }

        // Update the local colors in the new bitmap's palette.
        for (int i = 0; i < 16; ++i)
        {
            for (int j = 15; j >= 0; --j)
            {
                if (palBitField[i][j])
                {
                    // Get the new RGB color value.
                    uint8_t r = buffer[0];
                    uint8_t g = buffer[1];
                    uint8_t b = buffer[2];
                    buffer.erase(buffer.begin(), buffer.begin() + 3); // Erase the processed bytes.

                    // Calculate the palette index to be updated.
                    int palIndex = i * 16 + (15 - j);
                    // Assuming the palette is in RGB format, each color takes 3 bytes.
                    deltaBitmapData[palIndex * 3] = r;
                    deltaBitmapData[palIndex * 3 + 1] = g;
                    deltaBitmapData[palIndex * 3 + 2] = b;
                }
            }
        }
    }

    int blocksPerRow = 640 / 4; // Bitmap width is 640 pixels and each block is 4 pixels wide.
    int width = 640 * 3;        // Bitmap width is 640 pixels. Multiply by 3 for RGB.
    int blockNumber = 0;        // Define blockNumber outside the while loop

    std::cout << "Processing delta bitmap data..." << std::endl;

    while (!buffer.empty())
    {
        uint8_t opcode = buffer[0];
        buffer.erase(buffer.begin());

        std::cout << "opcode: 0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(opcode) << std::endl;
        std::cout << "buffer size: " << std::dec << buffer.size() << std::endl;
        std::cout << "block number: " << std::dec << blockNumber << std::endl;

        if (opcode >= 0x00 && opcode <= 0x5f)
        {
            // Followed by two parameters, which are hereby referred to as colours c1 and c0.
            uint8_t c1 = buffer[0];
            buffer.erase(buffer.begin());
            uint8_t c0 = buffer[0];
            buffer.erase(buffer.begin());

            // The Colour Map used is extracted from a predefined array of uint16 values containing 96 entries.
            uint16_t colourMap = PREDEFINED_COLOUR_MAP[opcode];

            // Calculate the block number based on the original and current size of the buffer.
            size_t totalBlocks = originalBufferSize / 3; // Assume 3 bytes per block (opcode and two color parameters).
            size_t remainingBlocks = buffer.size() / 3;
            size_t blockNumber = totalBlocks - remainingBlocks;

            // Iterate over the 16 pixels in the current block.
            for (int i = 0; i < 16; ++i)
            {
                // Determine the colour for the current pixel based on the colour map.
                uint8_t colour = (colourMap & (1 << i)) ? c1 : c0;

                // Calculate the position of the current pixel in the deltaBitmapData and staticBitmap.
                size_t blockRow = blockNumber / blocksPerRow; // blocksPerRow is width of the image in blocks.
                int blockCol = blockNumber % blocksPerRow;

                int pixelRow = i / 4; // Within the block, pixels are arranged in a 4x4 grid.
                int pixelCol = i % 4;

                size_t position = ((blockRow * 4 + pixelRow) * width + blockCol * 4 + pixelCol) * 3; // Multiply by 3 for RGB.

                // Store the new color to the deltaBitmapData.
                deltaBitmapData[position] = colour;
            }
        }
        else if (opcode == 0x60)
        {
            // Calculate the block number based on the original and current size of the buffer.
            size_t totalBlocks = originalBufferSize - 1; // -1 because this opcode has no parameters.
            size_t remainingBlocks = buffer.size();
            size_t blockNumber = totalBlocks - remainingBlocks;

            // Iterate over the 16 pixels in the current block.
            for (int i = 0; i < 16; ++i)
            {
                // Determine the colour for the current pixel based on the next parameter in the buffer.
                uint8_t colour = buffer[0];
                buffer.erase(buffer.begin());

                // Calculate the position of the current pixel in the deltaBitmapData and staticBitmap.
                size_t blockRow = blockNumber / blocksPerRow;
                int blockCol = blockNumber % blocksPerRow;

                int pixelRow = i / 4; // Within the block, pixels are arranged in a 4x4 grid.
                int pixelCol = i % 4;

                size_t position = ((blockRow * 4 + pixelRow) * width + blockCol * 4 + pixelCol) * 3; // Multiply by 3 for RGB.

                // Store the new color to the deltaBitmapData.
                deltaBitmapData[position] = colour;
            }
        }
        else if (opcode == 0x61)
        {
            // Calculate blocksPerRow.
            int blocksPerRow = 640 / 4; // Bitmap width is 320 pixels and each block is 4 pixels wide.

            // Increase the block number by blocksPerRow to skip one line.
            blockNumber += blocksPerRow;
        }
        else if (opcode >= 0x62 && opcode <= 0x6b)
        {
            int blocksToSkip = opcode - 0x62; // Calculate the number of blocks to skip.
            blockNumber += blocksToSkip;      // Move the current position by skipping the calculated number of blocks.
        }
        else if (opcode >= 0x6c && opcode <= 0x75)
        {
            uint8_t colour = buffer[0];
            buffer.erase(buffer.begin()); // Erase the processed byte.

            int blocksToFill = opcode - 0x6b;

            for (int filledBlocks = 0; filledBlocks < blocksToFill; ++filledBlocks)
            {
                for (int i = 0; i < 16; ++i)
                {
                    int blockRow = blockNumber / blocksPerRow; // blocksPerRow is width of the image in blocks.
                    int blockCol = blockNumber % blocksPerRow;

                    int pixelRow = i / 4; // Within the block, pixels are arranged in a 4x4 grid.
                    int pixelCol = i % 4;

                    int position = ((blockRow * 4 + pixelRow) * width + blockCol * 4 + pixelCol) * 3; // Multiply by 3 for RGB.

                    deltaBitmapData[position] = colour;
                }
                blockNumber++; // Move to the next block.
            }
        }
        else if (opcode >= 0x76 && opcode <= 0x7f)
        {
            int blocksToFill = opcode - 0x75;
            std::cout << "blocksToFill: " << blocksToFill << std::endl;

            for (int filledBlocks = 0; filledBlocks < blocksToFill; ++filledBlocks)
            {
                // Ensure buffer is not empty.
                if (buffer.empty())
                {
                    std::cerr << "Error: Buffer is empty. Cannot read colour parameter." << std::endl;
                    break;
                }

                // Read the colour parameter.
                uint8_t colour = buffer[0];
                buffer.erase(buffer.begin()); // Erase the processed byte.

                std::cout << "Processing block: " << filledBlocks + 1
                          << " of " << blocksToFill
                          << " with colour: " << static_cast<int>(colour) << std::endl;

                // Fill the block with the colour.
                for (int i = 0; i < 16; ++i)
                {
                    int blockRow = blockNumber / blocksPerRow; // blocksPerRow is width of the image in blocks.
                    int blockCol = blockNumber % blocksPerRow;

                    int pixelRow = i / 4; // Within the block, pixels are arranged in a 4x4 grid.
                    int pixelCol = i % 4;

                    int position = ((blockRow * 4 + pixelRow) * width + blockCol * 4 + pixelCol) * 3; // Multiply by 3 for RGB.

                    if (position >= deltaBitmapData.size())
                    {
                        std::cerr << "Error: Position out of bounds. Position: "
                                  << position
                                  << ", deltaBitmapData size: "
                                  << deltaBitmapData.size() << std::endl;
                        break;
                    }

                    deltaBitmapData[position] = colour;
                }
                blockNumber++; // Move to the next block.
                std::cout << "Finished processing block. Moving to block number: " << blockNumber << std::endl;
            }
        }
        else if (opcode >= 0x80 && opcode <= 0xff)
        {
            // Extract the Colour Map from the opcode and the following byte.
            uint16_t colourMap = opcode << 8;
            colourMap |= buffer[0];
            buffer.erase(buffer.begin()); // Erase the processed byte.

            // Read the colours c1 and c0.
            uint8_t c1 = buffer[0];
            buffer.erase(buffer.begin()); // Erase the processed byte.
            uint8_t c0 = buffer[0];
            buffer.erase(buffer.begin()); // Erase the processed byte.

            // Colour the block.
            for (int i = 0; i < 16; ++i)
            {
                // Determine the colour for the current pixel based on the Colour Map.
                uint8_t colour = (colourMap & (1 << i)) ? c1 : c0;

                // Calculate the position of the current pixel in the deltaBitmapData and staticBitmap.
                int blockRow = blockNumber / blocksPerRow; // blocksPerRow is width of the image in blocks.
                int blockCol = blockNumber % blocksPerRow;

                int pixelRow = i / 4; // Within the block, pixels are arranged in a 4x4 grid.
                int pixelCol = i % 4;

                int position = ((blockRow * 4 + pixelRow) * width + blockCol * 4 + pixelCol) * 3; // Multiply by 3 for RGB.

                deltaBitmapData[position] = colour;
            }
            blockNumber++; // Move to the next block.
        }
        // Remove later
        std::cout << "\nPress any key to continue...\n";
        std::cin.get();
    }

    std::cout << "Decoded " << blockNumber << " blocks." << std::endl;

    return deltaBitmapData;
}