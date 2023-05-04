@echo off
setlocal

set CONFIG=Release
set PLATFORM=x64

cls

if exist bin\ (
    echo Cleaning build files...
    for /d %%i in (bin obj) do (
        for /r "%%i" %%j in (*) do (
            del /f /q "%%j"
        )
    )
)

set OUTPUT_DIR=bin\%PLATFORM%_%CONFIG%
set INTERMEDIATE_DIR=obj\%PLATFORM%_%CONFIG%

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%

echo Building %CONFIG% %PLATFORM% configuration...

echo Compiling source files...
for %%i in (src\*.cpp) do (
    cl /nologo /W3 /WX- /EHsc /MD /GS /std:c++17 /Fo"%INTERMEDIATE_DIR%\%%~ni.obj" /c /I include "%%i"
)

echo Linking...
link /NOLOGO /SUBSYSTEM:CONSOLE /INCREMENTAL:NO /ENTRY:mainCRTStartup /OUT:"%OUTPUT_DIR%\v64-tng.exe" %INTERMEDIATE_DIR%\*.obj /LIBPATH:"C:\libs"

endlocal
