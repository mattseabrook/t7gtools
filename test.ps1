# Define the format of the Markdown table header
$markdownHeader = '| Index | chunkType | dataSize | lengthMask | lengthBits | Type | Compressed |
| --- | --- | --- | --- | --- | --- | --- |
'

# Set the path to the directory containing the VDX files
$dirPath = ".\DR\"

# Get a list of all the VDX files in the directory
$vdxFiles = Get-ChildItem $dirPath -Filter "*.vdx"

# Loop through each VDX file and parse the header and smaller files
foreach ($file in $vdxFiles) {
  # Open the file and read the header
  $stream = [System.IO.File]::OpenRead($file.FullName)
  $binaryReader = New-Object System.IO.BinaryReader($stream)
  $identifier = $binaryReader.ReadUInt16()
  $unknownBytes = $binaryReader.ReadBytes(6)

  # Pretty print the header information
  Write-Host "$($file.Name)`n"
  Write-Host "    Identifier: 0x$($identifier.ToString('X4'))"
  Write-Host "    Unknown: 0x$($unknownBytes[0].ToString('X2')) 0x$($unknownBytes[1].ToString('X2')) 0x$($unknownBytes[2].ToString('X2')) 0x$($unknownBytes[3].ToString('X2')) 0x$($unknownBytes[4].ToString('X2')) 0x$($unknownBytes[5].ToString('X2'))`n"

  # Parse the smaller files and create the Markdown table
  $markdown = $markdownHeader
  $index = 0
  while ($stream.Position -lt $stream.Length) {
    $chunkType = $binaryReader.ReadByte()
    $unknown1 = $binaryReader.ReadByte()
    $dataSize = $binaryReader.ReadUInt32()
    $lengthMask = $binaryReader.ReadByte()
    $lengthBits = $binaryReader.ReadByte()

    # Determine the type of the smaller file based on the chunk type
    if ($chunkType -eq 0x00) {
      $type = "Replay"
    } elseif ($chunkType -eq 0x20) {
      $type = "Bitmap"
    } elseif ($chunkType -eq 0x25) {
      $type = "Delta Frame"
    } elseif ($chunkType -eq 0x80) {
      $type = "Raw WAV data - 8-bit, Mono, 22kHz"
    } else {
      $type = "Unknown"
    }

    # Determine if the smaller file is compressed based on the lengthMask and lengthBits values
    if ($lengthMask -eq 0 -and $lengthBits -eq 0) {
      $compressed = "false"
    } else {
      $compressed = "true"
    }

    # Add the smaller file information to the Markdown table
    $markdown += '| ' + $index + ' | 0x' + $chunkType.ToString('X2') + ' | ' + $dataSize.ToString('N0') + ' | 0x' + $lengthMask.ToString('X2') + ' | 0x' + $lengthBits.ToString('X2') + ' | ' + $type + ' | ' + $compressed + ' |
'
    $index++
    # Skip over the actual data of the smaller file
    $stream.Seek($dataSize, [System.IO.SeekOrigin]::Current) | Out-Null
  }

  Write-Host $markdown
  Write-Host ""   
  
  # Close the file stream
  $stream.Close()
}
