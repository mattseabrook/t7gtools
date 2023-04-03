@echo off
setlocal

set PROJECT_ROOT=E:\t7gtools
set INCLUDE_DIRS=C:\libs\glfw-3.3.8.bin.WIN64\include
set LIB_DIRS=C:\libs\glfw-3.3.8.bin.WIN64\lib-vc2022

set CL_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\cl.exe"
set LINK_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\link.exe"

set CL_ARGS=/std:c++latest /EHsc /O2 /I"%INCLUDE_DIRS%"
set LINK_ARGS=/SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LIBPATH:"%LIB_DIRS%" glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib

set SOURCE_FILES=%PROJECT_ROOT%\src\*.cpp

%CL_PATH% %CL_ARGS% %SOURCE_FILES%
%LINK_PATH% %LINK_ARGS%

endlocal"
