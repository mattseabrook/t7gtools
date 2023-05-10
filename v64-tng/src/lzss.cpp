// lzss.cpp

#include <vector>
#include <cstdint>

#include "vdx.h"

// Decompress the VDX data
std::vector<uint8_t> lzssDecompress(const std::vector<uint8_t> &compressedData, uint8_t lengthMask, uint8_t lengthBits)
{
    const uint32_t N = 1 << (16 - lengthBits);
    const uint32_t F = 1 << lengthBits;
    const uint32_t threshold = 3;

    std::vector<uint8_t> decompressedData;
    std::vector<uint8_t> his_buf(N);
    uint32_t his_buf_pos = N - F;

    size_t in_buf_pos = 0;
    uint32_t out_buf_pos = 0;

    while (in_buf_pos < compressedData.size() - 1)
    {
        uint8_t flags = compressedData[in_buf_pos++];
        for (uint32_t i = 0; i < 8 && in_buf_pos < compressedData.size() - 1; ++i)
        {
            if ((flags & 1) == 0)
            {
                uint16_t ofs_len = compressedData[in_buf_pos++] | (compressedData[in_buf_pos++] << 8);
                if (ofs_len == 0)
                {
                    break;
                }

                uint32_t length = (ofs_len & lengthMask) + threshold;
                uint32_t offset = (his_buf_pos - (ofs_len >> lengthBits)) & (N - 1);

                for (uint32_t j = 0; j < length; ++j)
                {
                    uint8_t b = his_buf[(offset + j) & (N - 1)];
                    decompressedData.push_back(b);
                    his_buf[his_buf_pos] = b;
                    his_buf_pos = (his_buf_pos + 1) & (N - 1);
                }
            }
            else
            {
                uint8_t b = compressedData[in_buf_pos++];
                decompressedData.push_back(b);
                his_buf[his_buf_pos] = b;
                his_buf_pos = (his_buf_pos + 1) & (N - 1);
            }
            flags >>= 1;
        }
    }

    return decompressedData;
}