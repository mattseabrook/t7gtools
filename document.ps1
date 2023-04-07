$inputFile = $args[0]

if (-not ($inputFile -match '\.rl$')) {
    Write-Host "Invalid input file. Please provide a *.rl file."
    exit
}

$markdownFile = $inputFile -replace '\.rl$', '.md'
$HTMLFile = $inputFile -replace '\.rl$', '.html'

$markdownContent = Get-Content -Path $markdownFile
$markdownContent = $markdownContent[2..($markdownContent.Length - 1)]

$convertedRows = @()
$additionalContent = @()

foreach ($line in $markdownContent) {
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
        width: 5%;
    }
    .cell:nth-child(2) {
        width: 5%;
    }
    .cell:nth-child(3) {
        width: 5%;
    }
    .cell:nth-child(4) {
        width: 65%;
    }
</style>
"@

$JavaScript = @"
<script>
    function sortTable(column, dataType) {
        const table = document.querySelector('.table-responsive');
        const rows = Array.from(table.querySelectorAll('.row:not(.header)'));
        const sortType = table.getAttribute('data-sort-type') === 'asc' ? 'desc' : 'asc';
        table.setAttribute('data-sort-type', sortType);

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
    }
</script>
"@

# Create the final HTML content
$html = @"
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Markdown to DIV Table</title>
    $CSS
</head>
<body>
    <h1>$($inputFile.Split("\")[-1])</h1>
    <div class="table-responsive" data-sort-type="asc">
        <div class="row header">
            <div class="cell" onclick="sortTable(0, 'string')">Filename</div>
            <div class="cell" onclick="sortTable(1, 'int')">Size</div>
            <div class="cell" onclick="sortTable(2, 'int')">GJD Index</div>
            <div class="cell" onclick="sortTable(3, 'string')">Description</div>
        </div>
        $convertedRowsString
    </div>
    $additionalContentString
    $JavaScript
</body>
</html>
"@

Write-Host $html    # Echo and write HTML to file

if (Test-Path -Path $HTMLFile) {
    Remove-Item -Path $HTMLFile
}
$html | Set-Content -Path $HTMLFile