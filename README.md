# OpenGL 4.1 C++20 Project

A modern OpenGL 4.1 application written in C++20 with cross-platform support for Windows (MSVC), macOS (Clang), and Linux (GCC/Clang).

## Cloning
```bash
git clone --recursive git@github.com:pmariniutec/cg-opengl-base.git
```

## Project Structure

```
utec/
├── build/                        # CMake build directory
├── external/
│   ├── glm/                      # GLM library (submodule)
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
- OpenGL 4.1 compatible graphics card and drivers

### Windows
- Windows 10/11
- Visual Studio 2019 or 2022 (with C++ development tools)
- Windows 10 SDK
- clang-cl should work but not tested at the moment

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

## Building the Project

### Using Command Line

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

## OpenGL 4.1 Features Used

- **Core Profile**: No deprecated OpenGL functionality
- **Vertex Array Objects**: Modern vertex specification
- **Programmable Pipeline**: Custom vertex and fragment shaders  
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

This project is provided as a template for educational and development purposes.

## Contributing

Feel free to submit issues and pull requests to improve this OpenGL template project.
