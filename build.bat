@echo off
REM SmallBiz Build Script for Windows
REM This script compiles the inventory management system

echo.
echo =============================================
echo   SmallBiz Inventory System - Build Script
echo =============================================
echo.

REM Check for Visual Studio Developer Command Prompt
where cl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [Found] MSVC Compiler
    echo Compiling with MSVC...
    
    if not exist "build" mkdir build
    cl /EHsc /Fe:SmallBiz.exe src\main.cpp src\Product.cpp src\PhysicalProduct.cpp src\DigitalProduct.cpp src\Inventory.cpp /Fobuild\
    
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo [SUCCESS] Build complete! Run SmallBiz.exe to start.
    ) else (
        echo.
        echo [ERROR] Build failed.
    )
    goto :end
)

REM Check for MinGW g++
where g++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [Found] MinGW GCC Compiler
    echo Compiling with g++...
    
    if not exist "build" mkdir build
    g++ -std=c++17 -Wall -o SmallBiz.exe src\main.cpp src\Product.cpp src\PhysicalProduct.cpp src\DigitalProduct.cpp src\Inventory.cpp
    
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo [SUCCESS] Build complete! Run SmallBiz.exe to start.
    ) else (
        echo.
        echo [ERROR] Build failed.
    )
    goto :end
)

echo [ERROR] No C++ compiler found!
echo.
echo Please install one of the following:
echo   1. Visual Studio with C++ workload
echo      - Run from "Developer Command Prompt for VS"
echo.
echo   2. MinGW-w64 (GCC for Windows)
echo      - Download from: https://www.mingw-w64.org/
echo      - Add bin folder to PATH
echo.
echo   3. Visual Studio Code with C/C++ Extension
echo      - Install ms-vscode.cpptools extension
echo      - Configure tasks.json for compilation
echo.

:end
echo.
pause
