# OpenGL 4.5 C++20 Project

A modern OpenGL 4.5 application written in C++20 with cross-platform support for Windows (MSVC), macOS (Clang), and Linux (GCC/Clang). This project demonstrates setting up a complete OpenGL development environment with modern C++ practices.

## Features

- **OpenGL 4.5 Core Profile**: Using the latest OpenGL features with vertex array objects
- **C++20 Standard**: Modern C++ with latest language features and smart pointers
- **Cross-Platform Support**: Windows (MSVC), macOS (Clang), Linux (GCC/Clang)  
- **GLFW 3.3**: Cross-platform window management and input handling
- **GLAD**: OpenGL function loader for accessing modern OpenGL functions
- **GLM**: Header-only mathematics library for 3D transformations
- **CMake Build System**: Cross-platform build configuration with platform detection
- **Interactive 3D Scene**: Unity-style camera controls with mouse and WASD movement
- **Multiple Rendering Modes**: Points, lines, and 3D cubes with Phong lighting
- **Dual Shader System**: Separate shaders for 3D lighting and 2D vertex colors
- **VS Code Integration**: Complete development environment with cross-platform tasks

## Project Structure

```
utec/
├── .github/
│   └── copilot-instructions.md    # GitHub Copilot instructions
├── .vscode/
│   ├── tasks.json                 # Build and run tasks
│   ├── launch.json               # Debug configuration
│   ├── c_cpp_properties.json     # IntelliSense configuration
│   └── settings.json             # VS Code settings
├── build/                        # CMake build directory
├── external/
│   ├── glfw/                     # GLFW library (submodule)
│   └── glad/                     # GLAD OpenGL loader
├── include/
│   ├── Application.h             # Main application class
│   ├── Shader.h                  # Shader management
│   └── Renderer.h                # Rendering utilities
├── shaders/
│   ├── vertex.glsl               # Vertex shader (GLSL 4.50)
│   └── fragment.glsl             # Fragment shader (GLSL 4.50)
├── src/
│   ├── main.cpp                  # Application entry point
│   ├── Application.cpp           # Application implementation
│   ├── Shader.cpp                # Shader loading and compilation
│   └── Renderer.cpp              # Rendering implementation
├── CMakeLists.txt                # Main CMake configuration
└── README.md                     # This file
```

## Requirements

### All Platforms
- CMake 3.20 or later
- OpenGL 4.5 compatible graphics card and drivers

### Windows
- Windows 10/11
- Visual Studio 2019 or 2022 (with C++ development tools)
- Windows 10 SDK

### macOS  
- macOS 10.15 or later
- Xcode Command Line Tools
- Clang compiler (included with Xcode)

### Linux
- GCC 10+ or Clang 10+ compiler
- Development packages: `libgl1-mesa-dev libxi-dev libxcursor-dev libxrandr-dev libxinerama-dev`
- pkg-config

## Building

### CMake Commands

The project uses pure CMake for cross-platform building. No external scripts required.

**Windows (Visual Studio):**
```batch
# Configure
cmake -G "Visual Studio 17 2022" -A x64 -S . -B build

# Build Debug
cmake --build build --config Debug --parallel

# Build Release
cmake --build build --config Release --parallel

# Run
cd build\bin\Debug && OpenGLApp.exe
```

**macOS/Linux (Unix Makefiles):**
```bash
# Configure Debug
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -S . -B build

# Configure Release  
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build
cmake --build build --parallel

# Run
cd build/bin && ./OpenGLApp
```

### VS Code Integration

The project includes cross-platform VS Code tasks that use pure CMake:

1. Open Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`)
2. Select "Tasks: Run Task"  
3. Choose from available tasks:
   - **CMake Configure Cross-Platform**: Configure for current platform
   - **CMake Build Cross-Platform Debug**: Build in Debug mode
   - **Cross-Platform Run**: Build and run the application

### Build Information

When configuring, CMake will display helpful information:
- Detected platform and compiler
- Build type and output directories  
- Platform-specific build commands
- Shader handling method

## Running the Application

**Windows:**
```batch
cd build\bin\Debug
OpenGLApp.exe
```

**macOS/Linux:**
```bash
cd build/bin
./OpenGLApp
```

## Controls

- **Right-click + drag**: Rotate camera around the scene (Unity-style)
- **WASD keys**: Move camera forward/back/left/right (while holding right-click)
- **ESC**: Exit application
- Git (for cloning dependencies)
- Graphics card with OpenGL 4.5 support

## Building the Project

### Option 1: Using VS Code (Recommended)

1. Open the project folder in VS Code
2. Install recommended extensions:
   - C/C++ Extension Pack
   - CMake Tools
   - Shader languages support
3. Press `Ctrl+Shift+P` and run "CMake: Configure"
4. Press `Ctrl+Shift+P` and run "Tasks: Run Task" → "Build and Copy Shaders"
5. Press `F5` to build and run with debugging

### Option 2: Using Command Line

```powershell
# Navigate to project directory
cd "c:\Users\YourName\Development\utec"

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Debug

# Copy shaders to build directory
xcopy ..\shaders .\bin\Debug\shaders\ /E /I /Y

# Run the application
.\bin\Debug\OpenGLApp.exe
```

## Development Workflow

### Building
- Use `Ctrl+Shift+P` → "Tasks: Run Task" → "CMake Build Debug" for regular builds
- Use "Build and Copy Shaders" task to build and copy shader files automatically

### Running
- Press `F5` to run with debugging
- Use "Run Application" task to run without debugging
- The application will open a window showing a colored triangle

### Debugging
- Set breakpoints in VS Code
- Press `F5` to start debugging
- Use the Debug Console for OpenGL error checking

## Code Structure

### Application Class
The main `Application` class handles:
- GLFW window creation and management
- OpenGL context initialization  
- Input processing
- Main render loop
- Resource cleanup

### Shader Class
The `Shader` class provides:
- GLSL shader loading from files
- Shader compilation with error checking
- Uniform variable management
- Program linking and validation

### Renderer Class
The `Renderer` class handles:
- Vertex Array Object (VAO) management
- Vertex Buffer Object (VBO) setup
- Basic geometry rendering
- OpenGL state management

## OpenGL 4.5 Features Used

- **Core Profile**: No deprecated OpenGL functionality
- **Vertex Array Objects**: Modern vertex specification
- **Programmable Pipeline**: Custom vertex and fragment shaders  
- **GLSL 4.50**: Modern shader language features
- **Debug Output**: OpenGL error reporting and validation

## Customization

### Adding New Shaders
1. Create `.glsl` files in the `shaders/` directory
2. Load them using the `Shader` class constructor
3. Shaders are automatically copied to build directory

### Adding Geometry
1. Extend the `Renderer` class with new setup methods
2. Create appropriate vertex data structures
3. Set up VAOs and VBOs for new geometry types

### Adding Libraries
1. Add subdirectories to `external/CMakeLists.txt`
2. Link libraries in `src/CMakeLists.txt`
3. Update include directories as needed

## Troubleshooting

### Build Issues
- Ensure Visual Studio C++ tools are installed
- Check CMake version (3.20+ required)
- Verify MSVC compiler is in PATH

### Runtime Issues
- Check graphics drivers support OpenGL 4.5
- Ensure shader files are in the correct directory
- Check console output for OpenGL error messages

### Shader Issues
- Verify GLSL version matches (`#version 450 core`)
- Check shader compilation errors in console output
- Ensure vertex attributes match between shaders and C++ code

## License

This project is provided as a template for educational and development purposes.

## Contributing

Feel free to submit issues and pull requests to improve this OpenGL template project.
