# document.ps1 - The 7th Guest : Documentation Tools
# Author: Matt Seabrook, 2023

# This script is used to generate the HTML documentation for the 7th Guest.


<#
.SYNOPSIS
Converts a binary file to a Markdown table.

.DESCRIPTION
This function takes in the path of a binary file as input, extracts data from the file, sorts it by size in descending order, and generates a Markdown table that displays the extracted data. The table includes columns for Filename, Size (in bytes), GJD Index, and Description.

.PARAMETER Path
The path of the binary file to convert to a Markdown table.

.EXAMPLE
Convert-RLToMarkdownTable -Path $inputFile

This example converts the binary file located at $inputFile to a Markdown table and returns the table as a string.

.OUTPUTS
A string representing the Markdown table that displays the extracted data.

#>
function Convert-RLToMarkdownTable {
    [CmdletBinding()]
    param (
        [Parameter(Mandatory = $true)]
        [string]$Path
    )

    # Open the binary file
    $binaryFile = Get-Content -Path $Path -Encoding Byte

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

    # Generate the Markdown table
    $header = @'
| Filename | Size (Bytes) | GJD Index | Description |
| --- | --- | --- | --- |
'@

    foreach ($item in $dataList) {
        $filename = $item.Filename
        $size = "{0:N0}" -f $item.Size
        $gjdIndex = $item.GjdIndex
        $markdown += "| $filename | $size | $gjdIndex |  |`n"
    }

    # Return the Markdown table
    return $markdown
}


<#
.SYNOPSIS
   This function reads binary data from a file and extracts header and smaller file information.
.DESCRIPTION
   This function takes two integer parameters: index and bytes, which represent the offset and number of bytes to read from the file. It then opens the binary file specified by the $inputFile variable, seeks to the specified offset, and reads the specified number of bytes. After that, it extracts the header information from the binary data, constructs an HTML structure containing the header information, and parses the rest of the binary data to create a Markdown table of smaller file information. Finally, it returns the HTML and Markdown as output.

.PARAMETER index
   The offset in bytes to start reading the binary data.

.PARAMETER bytes
   The number of bytes to read from the binary data.

.EXAMPLE
   Get-VDXData -index 0 -bytes 1024
   This command reads 1024 bytes of binary data starting at offset 0 and returns an HTML structure containing header information and a Markdown table of all the header information of the smaller files that are contained within the larger VDX structure.

.OUTPUTS
   This function returns an array containing two strings: an HTML structure containing header information, and a Markdown table of smaller file information.
#>
function Get-VDXData {
        [CmdletBinding()]
    param (
        [Parameter(Mandatory = $true)]
        [string]$Path,
        [int]$index,
        [int]$bytes
    )
    
    $Path = $Path -replace '^\.\[\\\/]', ''
    $GJDFile = Join-Path -Path (Get-Location) -ChildPath $Path

    $stream = [System.IO.File]::OpenRead($GJDFile)
    $stream.Position = $index

    $VDXFile = New-Object Byte[] $bytes

    $stream.Read($VDXFile, 0, $bytes)
    $stream.Close()

    $identifier = [BitConverter]::ToUInt16($VDXFile, 0)
    $unknownBytes = $VDXFile[2..7]

    # Construct the HTML that contains the header information
    $html = "<p>`n"
    $html += "Identifier: <code>" + $identifier.ToString('X4') + "</code><br>`n"
    $html += "UnknownBytes: <code>0x" + $unknownBytes[0].ToString('X2') + "</code> <code>0x" + $unknownBytes[1].ToString('X2') + "</code> <code>0x" + $unknownBytes[2].ToString('X2') + "</code> <code>0x" + $unknownBytes[3].ToString('X2') + "</code> <code>0x" + $unknownBytes[4].ToString('X2') + "</code> <code>0x" + $unknownBytes[5].ToString('X2') + "</code>`n"
    $html += "</p>"
     
    # Create the Markdown table
    $header = '| Index | chunkType | dataSize | lengthMask | lengthBits | Type | Compressed |
    | --- | --- | --- | --- | --- | --- | --- |
    '

    $index = 8
    while ($index -lt $bytes) {
        # Read the header values for the current smaller file
        $chunkType = $VDXFile[$index]
        $unknownByte = $VDXFile[$index + 1]
        $dataSize = [BitConverter]::ToUInt32($VDXFile, $index + 2)
        $lengthMask = $VDXFile[$index + 6]
        $lengthBits = $VDXFile[$index + 7]

        # Determine the type of the smaller file based on the chunk type
        if ($chunkType -eq 0x00) {
        $type = "Replay"
        } elseif ($chunkType -eq 0x20) {
        $type = "Bitmap"
        } elseif ($chunkType -eq 0x25) {
        $type = "Delta"
        } elseif ($chunkType -eq 0x80) {
        $type = "WAV"
        } else {
        $type = "Unknown"
        }

        # Determine if the smaller file is compressed based on the lengthMask and lengthBits values
        if ($lengthMask -eq 0 -and $lengthBits -eq 0) {
        $compressed = "false"
        } else {
        $compressed = "true"
        }
        
        # Add the header information to the Markdown table
        $markdown += "| $index | 0x$($chunkType.ToString('X2')) | $($dataSize.ToString('N0')) | 0x$($lengthMask.ToString('X2')) | 0x$($lengthBits.ToString('X2')) | $type | $compressed |`n"

        # Increment the index to the next smaller file
        $index += 8 + $dataSize
    }

    # Create a custom object with named properties
    $output = New-Object -TypeName PSObject -Property @{
        HTML = $html
        Markdown = $markdown
    }

    return $output
}


#
# Main Entry Point
#
$inputFile = $args[0]

if (-not ($inputFile -match '\.rl$')) {
    Write-Host "Invalid input file. Please provide a *.rl file."
    exit
}

$RLMarkdownContent = Convert-RLToMarkdownTable -Path $inputFile
$RLentries = $RLMarkdownContent -split '\r?\n'      # Split the Markdown table into separate lines

$convertedRows = @()
$additionalContent = @()

foreach ($line in $RLentries) {
    if ($line -match '^\|[^|]*\|[^|]*\|[^|]*\|[^|]*\|\s*$') {
        $row = $line -replace '\|', '' -split '\s+'
        $filename = $row[1] -replace '(?<=\..{3}).*', ''
        $convertedRows += @"
<div class="row">
    <div class="cell"><a href="#$filename">$filename</a></div>
    <div class="cell">$($row[2])</div>
    <div class="cell">$($row[3])</div>
    <div class="cell">$($row[4])</div>
</div>
"@
        $VDXData = Get-VDXData -Path ($inputFile -replace '\.rl$', '.GJD') -index $row[3] -bytes ($row[2] -replace ',', '')

        $additionalContent += "<h2 id='$filename'>$filename</h2>"
        $additionalContent += "<h3>Header</h3>"
        $additionalContent += $VDXData.HTML

        $VDXDataEntries = $VDXData.Markdown -split '\r?\n'
        # Remove the last entry because it is empty
        $VDXDataEntries = $VDXDataEntries[0..($VDXDataEntries.Length - 2)]

        $VDXDataConvertedRows = @()

        foreach ($VDXDataLine in $VDXDataEntries) {
            if ($VDXDataLine -match '^|[^|]|[^|]|[^|]|[^|]|[^|]|[^|]|[^|]|\s$') {
                $VDXDataRow = $VDXDataLine -replace '\|', '' -split '\s+'
                $VDXDataConvertedRows += @"
<div class="row">
    <div class="cell">$($VDXDataRow[1])</div>
    <div class="cell"><code>$($VDXDataRow[2])</code></div>
    <div class="cell">$($VDXDataRow[3])</div>
    <div class="cell"><code>$($VDXDataRow[4])</code></div>
    <div class="cell"><code>$($VDXDataRow[5])</code></div>
    <div class="cell">$($VDXDataRow[6])</div>
    <div class="cell">$($VDXDataRow[7])</div>
</div>
"@
            }
        }

        $additionalContent += $VDXDataConvertedRows

        $additionalContent += '<span><a href="#">Back to the table</a></span>'
    }
}

$convertedRowsString = $convertedRows -join "`n"
$additionalContentString = $additionalContent -join "`n"

# Define the CSS and JavaScript code
$CSS = @"
<style>
    .table-responsive {
        display: table;
        width: 80%;
        border-collapse: collapse;
    }
    .row {
        display: table-row;
    }
    .header {
        background-color: #f2f2f2;
        font-weight: bold;
        cursor: pointer;
    }
    .cell {
        display: table-cell;
        padding: 8px;
        border: 1px solid #ddd;
    }
    .cell:nth-child(1) {
        width: 7.5%;
    }
    .cell:nth-child(2) {
        width: 7.5%;
    }
    .cell:nth-child(3) {
        width: 7.5%;
    }
    .cell:nth-child(4) {
        width: 56.5 %;
    }
</style>
"@

$JavaScript = @"
<script>
    function sortTable(column, dataType) {
        const table = document.querySelector('.table-responsive');
        const rows = Array.from(table.querySelectorAll('.row:not(.header)'));
        const currentSortType = table.getAttribute('data-sort-type');
        const currentSortedColumn = parseInt(table.getAttribute('data-sorted-column'), 10);
        const sortType = currentSortType === 'desc' && column === currentSortedColumn ? 'asc' : 'desc';
        table.setAttribute('data-sort-type', sortType);
        table.setAttribute('data-sorted-column', column);

        rows.sort((a, b) => {
            let aValue = a.children[column].innerText;
            let bValue = b.children[column].innerText;
            if (dataType === 'int') {
                aValue = parseInt(aValue.replace(/,/g, ''), 10);
                bValue = parseInt(bValue.replace(/,/g, ''), 10);
                return sortType === 'asc' ? aValue - bValue : bValue - aValue;
            }
            return sortType === 'asc' ? aValue.localeCompare(bValue) : bValue.localeCompare(aValue);
        });

        rows.forEach(row => table.appendChild(row));
        setSortedColumnIndicator(column, sortType);
    }

    function setSortedColumnIndicator(column, sortType) {
        const table = document.querySelector('.table-responsive');
        const columnHeader = table.querySelector('.header > .cell:nth-child(' + (column + 1) + ')');
        const sortedColumnIndicator = sortType === 'asc' ? '&uarr;' : '&darr;';
        const previousSortedColumn = parseInt(table.getAttribute('data-previous-sorted-column'), 10);

        if (previousSortedColumn >= 0) {
            const previousColumnHeader = table.querySelector('.header > .cell:nth-child(' + (previousSortedColumn + 1) + ')');
            previousColumnHeader.innerHTML = previousColumnHeader.innerHTML.slice(0, -1).trim(); // Remove last character (arrow)
        }

        columnHeader.innerHTML = columnHeader.innerHTML.trim() + ' ' + sortedColumnIndicator; // Add new arrow
        table.setAttribute('data-previous-sorted-column', column);
    }

    document.addEventListener('DOMContentLoaded', () => {
        sortTable(1, 'int');
    });
</script>
"@

# Create the final HTML content
$html = @"
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Index of $($inputFile.Split("\")[-1])</title>
    $CSS
    $JavaScript
</head>
<body>
    <h1>$($inputFile.Split("\")[-1])</h1>
    <div class="table-responsive" data-sort-type="desc">
        <div class="row header">
            <div class="cell" data-sort-type="desc" onclick="sortTable(0, 'string')">Filename</div>
            <div class="cell" data-sort-type="desc" onclick="sortTable(1, 'int')">Size</div>
            <div class="cell" data-sort-type="desc" onclick="sortTable(2, 'int')">GJD Index</div>
            <div class="cell" data-sort-type="desc" onclick="sortTable(3, 'string')">Description</div>
        </div>
        $convertedRowsString
    </div>
    <div class="vdx-info">
        $additionalContentString
    </div>
</body>
</html>
"@

Write-Host $html    # Echo and write HTML to file
$HTMLFile = $inputFile -replace '\.rl$', '.html'

if (Test-Path -Path $HTMLFile) {
    Remove-Item -Path $HTMLFile
}
$html | Set-Content -Path $HTMLFile