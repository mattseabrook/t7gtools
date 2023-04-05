procedure DecompressBlock(InBuf: TBuffer; BlockHeader: TBlockHeader;
  var OutBuf: TBuffer);
var
  N,
  F,
  Offset,
  Length,
  OfsLen   : Word;
  Threshold,
  Flags,
  b        : Byte;
  i, j,
  InBufPos,
  OutBufPos,
  HisBufPos: Longint;
  HisBuf   : TBuffer;
begin
  // initialize LZSS parameters for this block
  N := 1 shl ($f - BlockHeader.BitsForLen + 1);
  F := 1 shl (BlockHeader.BitsForLen);
  Threshold := 3;
  HisBufPos := N - F;

  SetLength(HisBuf, N);
  FillChar(HisBuf[0], N, 0);

  SetLength(OutBuf, 0);
  OutBufPos := 0;

  InBufPos := 0;

  // start extracting block contents
  while Longword(InBufPos) < BlockHeader.BlockSize - 1 do
  begin
    // read bit field 
    Flags := InBuf[InBufPos];
    Inc(InBufPos);

    // process bit field 
    for i := 1 to 8 do
    begin
      if Longword(InBufPos) < BlockHeader.BlockSize - 1 then
      begin
        // check for buffer window reference 
        if (Flags and 1 = 0) then
        begin
          // read offset and length 
          OfsLen := InBuf[InBufPos] + (InBuf[InBufPos + 1] shl 8);
          Inc(InBufPos, 2);

          // check for end marker 
          if OfsLen = 0 then
            Break;

          // derive offset and length values 
          Length := (OfsLen and BlockHeader.LengthMask) + Threshold;
          Offset := (HisBufPos - (OfsLen shr BlockHeader.BitsForLen))
            and (N - 1);

          // peek into buffer 
          SetLength(OutBuf, High(OutBuf) + Length + 1);
          for j := 0 to Length - 1 do
          begin
            b := HisBuf[(Offset + j) and (N - 1)];
            OutBuf[OutBufPos] := b;
            Inc(OutBufPos);
            HisBuf[HisBufPos] := b;
            HisBufPos := (HisBufPos + 1) and (N - 1)
          end
        end
        else
        // copy literally 
        begin
          SetLength(OutBuf, High(OutBuf) + 2);
          b := InBuf[InBufPos];
          Inc(InBufPos);
          OutBuf[OutBufPos] := b;
          HisBuf[HisBufPos] := b;
          Inc(OutBufPos);
          HisBufPos := (HisBufPos + 1) and (N - 1)
        end;

        Flags := Flags shr 1
      end
    end
  end
end;
