// lzss.cpp

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

#include "vdx.h"

// Decompress the VDX data
std::vector<uint8_t> lzssDecompress(const std::vector<uint8_t> &compressedData, int lengthMask, int lengthBits)
{
    // Initialize variables based on lengthBits
    const size_t N = 1 << (16 - lengthBits);
    const size_t F = 1 << lengthBits;
    const size_t threshold = 3;

    std::vector<uint8_t> decompressedData;
    std::vector<uint8_t> window(N, 0);
    size_t windowPos = N - F;

    // Iterate through the compressed data
    auto inputIter = compressedData.begin();
    while (inputIter != compressedData.end())
    {
        // Read the control byte
        uint8_t controlByte = *inputIter++;

        // Process each bit in the control byte
        for (int i = 0; i < 8 && inputIter != compressedData.end(); ++i)
        {
            // If the current bit is set
            if (controlByte & (1 << i))
            {
                // Read the offset and length combined value
                uint16_t offsetLength = *inputIter++;
                offsetLength |= static_cast<uint16_t>(*inputIter++) << 8;

                // Calculate the offset and length from the combined value
                size_t offset = (offsetLength >> lengthBits) & (N - 1);
                size_t length = (offsetLength & lengthMask) + threshold;

                // Copy bytes from the sliding window to the output
                for (size_t j = 0; j < length; ++j)
                {
                    uint8_t byte = window[(windowPos - offset) % N];
                    decompressedData.push_back(byte);
                    window[windowPos] = byte;
                    windowPos = (windowPos + 1) % N;
                }
            }
            else
            {
                // Copy the literal byte to the output and update the sliding window
                uint8_t byte = *inputIter++;
                decompressedData.push_back(byte);
                window[windowPos] = byte;
                windowPos = (windowPos + 1) % N;
            }
        }
    }

    return decompressedData;
}