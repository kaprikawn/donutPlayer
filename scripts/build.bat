@echo off
SET SCRIPT_DIR=%~dp0

pushd %SCRIPT_DIR%
cd ..
SET ROOT_DIR=%cd%
popd

SET BUILD_DIR=%ROOT_DIR%\build

SET VCVARS_DIR=C:\"Program Files"\"Microsoft Visual Studio"\2022\Community\VC\Auxiliary\Build\

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

pushd %BUILD_DIR%

call %VCVARS_DIR%\vcvarsall.bat x64

cl -Zi /EHsc -wd4312 -DDEBUG=1 /std:c++17 ..\src\main_windows.cpp /Fe"DonutPlayer.exe"
