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


#
#
#
function Get-VDXData {

}


#
# Main Entry Point
#
$inputFile = $args[0]

if (-not ($inputFile -match '\.rl$')) {
    Write-Host "Invalid input file. Please provide a *.rl file."
    exit
}

$HTMLFile = $inputFile -replace '\.rl$', '.html'

$RLMarkdownContent = Convert-RLToMarkdownTable -Path $inputFile

$convertedRows = @()
$additionalContent = @()

# Split the Markdown table into separate lines
$markdownLines = $RLMarkdownContent -split '\r?\n'

foreach ($line in $markdownLines) {
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
        $additionalContent += @"
<h2 id="$filename">$filename</h2>
<p>Placeholder for $filename file info</p>
<span><a href="#">Back to the table</a></span>
"@
    }
}

$convertedRowsString = $convertedRows -join "`n"
$additionalContentString = ($additionalContent | Sort-Object) -join "`n"

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
    <div class="table-responsive" data-sort-type="asc">
        <div class="row header">
            <div class="cell" data-sort-type="asc" onclick="sortTable(0, 'string')">Filename</div>
            <div class="cell" data-sort-type="desc" onclick="sortTable(1, 'int')">Size</div>
            <div class="cell" data-sort-type="asc" onclick="sortTable(2, 'int')">GJD Index</div>
            <div class="cell" data-sort-type="asc" onclick="sortTable(3, 'string')">Description</div>
        </div>
        $convertedRowsString
    </div>
    $additionalContentString
</body>
</html>
"@

Write-Host $html    # Echo and write HTML to file

if (Test-Path -Path $HTMLFile) {
    Remove-Item -Path $HTMLFile
}
$html | Set-Content -Path $HTMLFile