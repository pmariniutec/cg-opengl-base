@echo off
REM Cross-platform build script for Windows
REM Usage: build.bat [clean|debug|release]

set BUILD_DIR=build
set BUILD_TYPE=Debug

REM Parse command line arguments
if "%1"=="clean" (
    echo Cleaning build directory...
    rmdir /s /q "%BUILD_DIR%" 2>nul
    exit /b 0
)

if "%1"=="debug" (
    set BUILD_TYPE=Debug
) else if "%1"=="release" (
    set BUILD_TYPE=Release
) else if "%1"=="" (
    set BUILD_TYPE=Debug
) else (
    echo Usage: %0 [clean^|debug^|release]
    echo   clean   - Remove build directory
    echo   debug   - Build in Debug mode ^(default^)
    echo   release - Build in Release mode
    exit /b 1
)

echo Building OpenGL Project in %BUILD_TYPE% mode...

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Configure with CMake
echo Configuring project...
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

REM Build
echo Building project...
cmake --build . --config %BUILD_TYPE%
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo Build completed successfully!
echo Executable location: %BUILD_DIR%\bin\%BUILD_TYPE%\OpenGLApp.exe

cd ..
