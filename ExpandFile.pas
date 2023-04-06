procedure ExpandFile(VDXName: string);
var
  WAVOpen    : Boolean;
  InBuf,
  OutBuf     : TBuffer;
  BlockHeader: TBlockHeader;
begin
  WAVOpen := false;

  VidFrames := 0;
  VidAdded  := 0;
  AudFrames := 0;
  AudAdded  := 0;
  AudSize   := 0;

  // go through VDX blocks 
  while not Eof(VDXFile) do
  begin
    // read block header
    BlockRead(VDXFile, BlockHeader, SizeOf(TBlockHeader));

    // read block content 
    SetLength(InBuf, BlockHeader.BlockSize);
    BlockRead(VDXFile, InBuf[0], BlockHeader.BlockSize);

    // check block compression 
    if (BlockHeader.BitsForLen = 0) then
      OutBuf := Copy(InBuf)
      // ChatGPT - Write OutBuf as a binary file in the local directory named based on VDXName-00-BlockHeader.PlayCmd(uncompressed).bin, VDXName-01-BlockHeader.PlayCmd(uncompressed).bin, etc. You may have to alter the structure of the while loop to make a counter to keep track, etc. 
    else
    // ChatGPT - Write OutBuf as a binary file in the local directory named based on VDXName-00-BlockHeader.PlayCmd(compressed).bin, VDXName-01-BlockHeader.PlayCmd(compressed).bin you may have to alter the structure of the while loop to make a counter to keep track, etc.
      DecompressBlock(InBuf, BlockHeader, OutBuf);
      // ChatGPT - Write OutBuf as a binary file in the local directory named based on VDXName-00-BlockHeader.PlayCmd(decompressed).bin, VDXName-01-BlockHeader.PlayCmd(decompressed).bin you may have to alter the structure of the while loop to make a counter to keep track, etc.

    // check for known media type 
    case BlockHeader.BlockType of
        0: case BlockHeader.PlayCmd of
             103: WriteLn('  unsupported command ', BlockHeader.PlayCmd,
               ' found in block of type 0x00')
           end;
       32: case BlockHeader.PlayCmd of
             103: WriteBMP(VDXName, OutBuf);
             119: WriteBMP(VDXName, OutBuf)
           else
             WriteLn('  unsupported command ', BlockHeader.PlayCmd,
               ' found in block of type 0x20')
           end;
       37: case BlockHeader.PlayCmd of
             103: WriteVidFrame(VDXName, OutBuf);
             119: WriteVidFrame(VDXName, OutBuf)
           else
             WriteLn('  unsupported command ', BlockHeader.PlayCmd,
               ' found in block of type 0x25')
           end;
    else
      WriteLn('  unsupported block type 0x', IntToHex(BlockHeader.BlockType, 2),
        ' found')
    end;

    Finalize(InBuf);
    Finalize(OutBuf)
  end;
end;