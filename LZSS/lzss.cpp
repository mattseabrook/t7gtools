#include <cstdint>
#include <vector>

std::vector<uint8_t> DecompressBlock(const std::vector<uint8_t> &compressedBytes, uint8_t lengthBits, uint32_t blockSize)
{
    uint32_t N = 1 << (0xf - lengthBits + 1);
    uint32_t F = 1 << lengthBits;
    uint32_t Threshold = 3;
    uint8_t Flags = 0;
    uint8_t b = 0;
    uint8_t i = 0;
    uint8_t j = 0;

    uint32_t inputBufferPosition = 0;

    uint32_t historyBufferPosition = N - F;
    std::vector<uint8_t> historyBuffer(N, 0);

    std::vector<uint8_t> decompressedBytes;

    while (inputBufferPosition < blockSize - 1)
    {
        Flags = compressedBytes[inputBufferPosition];
        inputBufferPosition += 1;

        for (i = 0; i < 8; i++)
        {
            if (inputBufferPosition < blockSize - 1)
            {
                if ((Flags & 1) == 0)
                {
                    uint16_t OfsLen = compressedBytes[inputBufferPosition] + (compressedBytes[inputBufferPosition + 1] << 8);
                    inputBufferPosition += 2;

                    if (OfsLen == 0)
                    {
                        break;
                    }
                    uint32_t Length = (OfsLen & ((1 << lengthBits) - 1)) + Threshold;
                    uint32_t Offset = (historyBufferPosition - (OfsLen >> lengthBits)) & (N - 1);

                    for (j = 0; j < Length; j++)
                    {
                        b = historyBuffer[(Offset + j) & (N - 1)];
                        decompressedBytes.push_back(b);
                        historyBuffer[historyBufferPosition] = b;
                        historyBufferPosition = (historyBufferPosition + 1) & (N - 1);
                    }
                }
                else
                {
                    decompressedBytes.push_back(compressedBytes[inputBufferPosition]);
                    inputBufferPosition += 1;
                    historyBuffer[historyBufferPosition] = b;
                    historyBufferPosition = (historyBufferPosition + 1) & (N - 1);
                }

                Flags >>= 1;
            }
        }
    }

    return decompressedBytes;
}