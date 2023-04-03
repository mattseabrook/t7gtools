@echo off
setlocal

set CONFIG=Release
set PLATFORM=x64

if "%1" == "clean" (
    echo Cleaning build files...
    rmdir /s /q bin
    rmdir /s /q obj
    exit /b
)

if "%1" == "-target" (
    set CONFIG=%2
    set PLATFORM=%3
)

set OUTPUT_DIR=bin\%PLATFORM%_%CONFIG%
set INTERMEDIATE_DIR=obj\%PLATFORM%_%CONFIG%

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%

echo Building %CONFIG% %PLATFORM% configuration...

echo Compiling source files...
for %%i in (src\*.cpp) do (
    cl /nologo /W3 /WX- /EHsc /MD /GS /Fo"%INTERMEDIATE_DIR%\%%~ni.obj" /c /I include "%%i"
)

echo Linking...
link /NOLOGO /SUBSYSTEM:WINDOWS /INCREMENTAL:NO /ENTRY:WinMainCRTStartup /OUT:"%OUTPUT_DIR%\t7gtools.exe" %INTERMEDIATE_DIR%\*.obj glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib

endlocal
