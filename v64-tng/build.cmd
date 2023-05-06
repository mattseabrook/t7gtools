@echo off
setlocal

set CONFIG=Release
set PLATFORM=x64
set CLEAN_ARG=%1

set ZLIB_DIR=C:\libs\zlib-1.2.13
set ZLIB_BUILD_DIR=%ZLIB_DIR%\build
set LPNG_DIR=C:\libs\lpng1639
set LPNG_BUILD_DIR=C:\libs\lpng1639\build
set LPNG_BUILD_RELEASE_DIR=%LPNG_DIR%\build\Release

cls

if /I "%CLEAN_ARG%"=="clean" (
    if exist bin\ (
        echo Cleaning bin\ directory...
        rmdir /s /q bin
    )

    if exist obj\ (
        echo Cleaning obj\ directory...
        rmdir /s /q obj
    )

    endlocal
    exit /b 0
)

set OUTPUT_DIR=bin\%PLATFORM%_%CONFIG%
set INTERMEDIATE_DIR=obj\%PLATFORM%_%CONFIG%

if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %INTERMEDIATE_DIR% mkdir %INTERMEDIATE_DIR%

echo Building %CONFIG% %PLATFORM% configuration...

echo Compiling source files...
for %%i in (src\*.cpp) do (
    cl /nologo /W3 /WX- /EHsc /std:c++17 /MD /GS /Fo"%INTERMEDIATE_DIR%\%%~ni.obj" /c /I include /I "%ZLIB_DIR%" /I "%ZLIB_BUILD_DIR%" /I "%LPNG_DIR%" /I "%LPNG_BUILD_DIR%" /I "%LPNG_SCRIPTS_DIR%" "%%i"
)

echo Linking...
link /NOLOGO /SUBSYSTEM:CONSOLE /INCREMENTAL:NO /ENTRY:mainCRTStartup /OUT:"%OUTPUT_DIR%\v64-tng.exe" %INTERMEDIATE_DIR%\*.obj /LIBPATH:"C:\libs" /LIBPATH:"%ZLIB_BUILD_RELEASE_DIR%" /LIBPATH:"%LPNG_BUILD_RELEASE_DIR%" zlibstatic.lib libpng16_static.lib

endlocal
