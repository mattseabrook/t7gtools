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

if "%1" == "-target" (
    set CONFIG=%2
    set PLATFORM=%3
)

set GLFW_DIR=C:\libs\glfw-3.3.8.bin.WIN64
set GLFW_INCLUDE_DIR=%GLFW_DIR%\include
set GLFW_LIB_DIR=%GLFW_DIR%\lib-vc2022

set OUTPUT_DIR=bin\%PLATFORM%_%CONFIG%
set INTERMEDIATE_DIR=obj\%PLATFORM%_%CONFIG%

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%

echo Building %CONFIG% %PLATFORM% configuration...

echo Compiling source files...
for %%i in (src\*.cpp) do (
    cl /nologo /W3 /WX- /EHsc /MD /GS /Fo"%INTERMEDIATE_DIR%\%%~ni.obj" /c /I "%GLFW_INCLUDE_DIR%" /I include "%%i"
)

echo Linking...
link /NOLOGO /SUBSYSTEM:WINDOWS /INCREMENTAL:NO /ENTRY:WinMainCRTStartup /OUT:"%OUTPUT_DIR%\t7gtools.exe" %INTERMEDIATE_DIR%\*.obj "%GLFW_LIB_DIR%\glfw3.lib" opengl32.lib user32.lib gdi32.lib shell32.lib /LIBPATH:"%GLFW_LIB_DIR%"

bin\x64_Release\t7gtools.exe -d

endlocal