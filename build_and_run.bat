@echo off
setlocal enabledelayedexpansion

set FILES=

for /R "%~dp0" %%f in (*.cpp) do (
    set FILES=!FILES! "%%f"
)

if "!FILES!"=="" (
    echo No .cpp files.
    pause
    exit /b 1
)

C:\MinGW\bin\g++.exe !FILES! -std=c++17 -o "%~dp0MiniDesign.exe"

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    pause
    exit /b 1
)

"%~dp0MiniDesign.exe" "(5,0) (14,16) (23,0) (0,8) (0,0) (28,8)"

pause