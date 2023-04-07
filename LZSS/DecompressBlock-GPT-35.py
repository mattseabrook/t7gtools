def DecompressBlock(InBuf, BlockHeader, OutBuf):
    N = 1 << (0xf - BlockHeader.BitsForLen + 1)
    F = 1 << (BlockHeader.BitsForLen)
    Threshold = 3
    Flags = 0
    b = 0
    i = 0
    j = 0
    InBufPos = 0
    OutBufPos = 0
    HisBufPos = N - F
    HisBuf = [0] * N

    while InBufPos < BlockHeader.BlockSize - 1:
        Flags = InBuf[InBufPos]
        InBufPos += 1

        for i in range(8):
            if InBufPos < BlockHeader.BlockSize - 1:
                if Flags & 1 == 0:
                    OfsLen = InBuf[InBufPos] + (InBuf[InBufPos + 1] << 8)
                    InBufPos += 2

                    if OfsLen == 0:
                        break

                    Length = (OfsLen & BlockHeader.LengthMask) + Threshold
                    Offset = (HisBufPos - (OfsLen >> BlockHeader.BitsForLen)) & (N - 1)

                    for j in range(Length):
                        b = HisBuf[(Offset + j) & (N - 1)]
                        OutBuf[OutBufPos] = b
                        OutBufPos += 1
                        HisBuf[HisBufPos] = b
                        HisBufPos = (HisBufPos + 1) & (N - 1)
                else:
                    OutBuf.append(InBuf[InBufPos])
                    InBufPos += 1
                    HisBuf[HisBufPos] = b
                    OutBufPos += 1
                    HisBufPos = (HisBufPos + 1) & (N - 1)

                Flags >>= 1
    return OutBuf