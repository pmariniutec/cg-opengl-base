<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

# OpenGL 4.5 C++20 Cross-Platform Project Instructions

This is a modern OpenGL 4.5 application written in C++20 with cross-platform support for Windows (MSVC), macOS (Clang), and Linux (GCC/Clang). The project uses:

- **OpenGL 4.5 Core Profile**: Modern OpenGL with core profile, no deprecated functionality
- **C++20**: Latest C++ standard with modern features
- **GLFW 3.3**: Cross-platform window management and input handling
- **GLAD**: OpenGL function loader
- **GLM**: Header-only mathematics library for 3D transformations
- **CMake**: Cross-platform build system with platform-specific configurations
- **Multi-Compiler Support**: MSVC (Windows), GCC/Clang (Linux), Clang (macOS)

## Project Structure
- `src/` - Source code (main.cpp, Application.cpp, Shader.cpp, Renderer.cpp)
- `include/` - Header files (Application.h, Shader.h, Renderer.h)  
- `shaders/` - GLSL shader files (vertex.glsl, fragment.glsl)
- `external/` - Third-party dependencies (GLFW, GLAD)

## Key Guidelines
- Use modern C++20 features like smart pointers, auto, range-based for loops
- Follow RAII principles for resource management
- Use OpenGL 4.5 core profile functions only
- Implement proper error checking for OpenGL calls
- Use vertex array objects (VAOs) for all geometry
- Shader version should be `#version 450 core`
- Window management through GLFW, not native platform APIs
- Use CMake for build configuration with platform-specific settings
- Support MSVC (Windows), GCC/Clang (Linux), and Clang (macOS) compilers

## Platform-Specific Considerations
### Windows (MSVC)
- Use Visual Studio generator for CMake
- Shader files linked via symbolic links to build output directories
- Multi-processor compilation enabled (`/MP`)
- CRT security warnings disabled for compatibility

### macOS (Clang)  
- Use Unix Makefiles generator
- Include `GL_SILENCE_DEPRECATION` to suppress OpenGL deprecation warnings
- Minimum deployment target: macOS 10.15 for C++20 support
- Shader files copied directly to build output

### Linux (GCC/Clang)
- Use Unix Makefiles generator  
- Enable comprehensive warnings (`-Wall -Wextra -Wpedantic`)
- Link with required system libraries via pkg-config
- Shader files copied directly to build output

## Common Patterns
- Initialize GLFW → Create window → Initialize GLAD → Setup OpenGL state
- All OpenGL resources should be properly cleaned up in destructors
- Use glGetError() or debug callbacks for error checking
- Shader compilation should include error checking and logging
- Cross-platform file path handling for shader loading
