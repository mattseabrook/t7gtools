# Open the binary file
$binaryFile = Get-Content -Path ".\dr.rl" -Encoding Byte

# Initialize an empty list to store the data
$dataList = @()

# Loop through the binary file, 20 bytes at a time
for ($i = 0; $i -lt $binaryFile.Length; $i += 20) {

    # Extract the filename, GJD index, and size in bytes
    $filenameBytes = $binaryFile[$i..($i + 11)]
    $filename = [System.Text.Encoding]::ASCII.GetString($filenameBytes)
    $gjdIndex = [BitConverter]::ToUInt32($binaryFile[($i + 12)..($i + 15)], 0)
    $size = [BitConverter]::ToUInt32($binaryFile[($i + 16)..($i + 19)], 0)

    # Create a custom object to store the extracted data
    $dataObject = New-Object -TypeName psobject -Property @{
        Filename = $filename
        GjdIndex = $gjdIndex
        Size = $size
        Description = $null
    }

    # Add the object to the list
    $dataList += $dataObject
}

# Sort the data by Size column in descending order
$dataList = $dataList | Sort-Object -Property Size -Descending

# Output the data in Markdown table format
Write-Output "| Filename | Size (Bytes) | GJD Index | Description |"
Write-Output "| --- | --- | --- | --- |"

# Copy the above text into a variable called $header
$header = @'
| Filename | Size (Bytes) | GJD Index | Description |
| --- | --- | --- | --- |
'@

if (Test-Path -Path ".\dr.md") {
    Remove-Item -Path ".\dr.md"
}

$header | Out-File -FilePath ".\dr.md" -Encoding ASCII

foreach ($item in $dataList) {
    $filename = $item.Filename
    $size = "{0:N0}" -f $item.Size
    $gjdIndex = $item.GjdIndex
    Write-Output "| $filename | $size | $gjdIndex |  |"
    "| $filename | $size | $gjdIndex |  |" | Out-File -FilePath ".\dr.md" -Append -Encoding ASCII
}