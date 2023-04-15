def DecompressBlock(compressedBytes, lengthBits, blockSize):
    N = 1 << (0xf - lengthBits + 1)
    F = 1 << lengthBits
    Threshold = 3
    Flags = 0
    b = 0
    i = 0
    j = 0
    inputBufferPosition = 0
    historyBufferPosition = N - F
    historyBuffer = [0] * N
    decompressedBytes = []
    outputBufferPosition = 0

    while inputBufferPosition < blockSize - 1:
        Flags = compressedBytes[inputBufferPosition]
        inputBufferPosition += 1

        for i in range(8):
            if inputBufferPosition < blockSize - 1:
                if Flags & 1 == 0:
                    OfsLen = compressedBytes[inputBufferPosition] + (compressedBytes[inputBufferPosition + 1] << 8)
                    inputBufferPosition += 2

                    if OfsLen == 0:
                        break
                    # Length may be wrong, and may have to use lengthMask
                    Length = (OfsLen & ((1 << lengthBits) - 1)) + Threshold
                    Offset = (historyBufferPosition - (OfsLen >> lengthBits)) & (N - 1)

                    for j in range(Length):
                        b = historyBuffer[(Offset + j) & (N - 1)]
                        decompressedBytes.append(b)
                        outputBufferPosition += 1
                        historyBuffer[historyBufferPosition] = b
                        historyBufferPosition = (historyBufferPosition + 1) & (N - 1)
                else:
                    decompressedBytes.append(compressedBytes[inputBufferPosition])
                    outputBufferPosition += 1
                    historyBuffer[historyBufferPosition] = b
                    inputBufferPosition += 1
                    historyBufferPosition = (historyBufferPosition + 1) & (N - 1)

                Flags >>= 1

    return decompressedBytes
