function decompressBlock(InBuf, BlockHeader, OutBuf) {
  var N,
    F,
    Offset,
    Length,
    OfsLen,
    Threshold,
    Flags,
    b,
    i,
    j,
    InBufPos,
    OutBufPos,
    HisBufPos,
    HisBuf;

  // initialize LZSS parameters for this block
  N = 1 << (0xf - BlockHeader.BitsForLen + 1);
  F = 1 << BlockHeader.BitsForLen;
  Threshold = 3;
  HisBufPos = N - F;

  HisBuf = new Array(N).fill(0);

  OutBuf = [];
  OutBufPos = 0;

  InBufPos = 0;

  // start extracting block contents
  while (InBufPos < BlockHeader.BlockSize - 1) {
    // read bit field
    Flags = InBuf[InBufPos];
    InBufPos++;

    // process bit field
    for (i = 1; i <= 8; i++) {
      if (InBufPos < BlockHeader.BlockSize - 1) {
        // check for buffer window reference
        if ((Flags & 1) == 0) {
          // read offset and length
          OfsLen = InBuf[InBufPos] + (InBuf[InBufPos + 1] << 8);
          InBufPos += 2;

          // check for end marker
          if (OfsLen == 0) {
            break;
          }

          // derive offset and length values
          Length = (OfsLen & BlockHeader.LengthMask) + Threshold;
          Offset = (HisBufPos - (OfsLen >> BlockHeader.BitsForLen)) & (N - 1);

          // peek into buffer
          for (j = 0; j < Length; j++) {
            b = HisBuf[(Offset + j) & (N - 1)];
            OutBuf[OutBufPos] = b;
            OutBufPos++;
            HisBuf[HisBufPos] = b;
            HisBufPos = (HisBufPos + 1) & (N - 1);
          }
        } else {
          // copy literally
          OutBuf[OutBufPos] = InBuf[InBufPos];
          InBufPos++;
          HisBuf[HisBufPos] = OutBuf[OutBufPos];
          OutBufPos++;
          HisBufPos = (HisBufPos + 1) & (N - 1);
        }

        Flags = Flags >> 1;
      }
    }
  }
}
