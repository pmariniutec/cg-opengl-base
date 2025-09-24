cmake_minimum_required(VERSION 3.20)
project(OpenGLProject VERSION 1.0.0)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /permissive-)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    # Enable multi-processor compilation
    message(STATUS "Using MSVC compiler")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
    # Enable debug symbols in Debug mode
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g)
    endif()
    # Enable optimizations in Release mode
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3)
    endif()
    message(STATUS "Using ${CMAKE_CXX_COMPILER_ID} compiler")
endif()

# Platform-specific configurations
if(APPLE)
    # macOS specific settings
    # Enable modern OpenGL on macOS
    add_compile_definitions(GL_SILENCE_DEPRECATION)
elseif(UNIX AND NOT APPLE)
    # Linux specific settings
    find_package(PkgConfig REQUIRED)
endif()

# Create output directories with proper configuration-based structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find packages
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found: ${OPENGL_gl_LIBRARY}")

# Add subdirectories
add_subdirectory(external)
add_subdirectory(src)

# Cross-platform shader handling
if(MSVC)
    # Multi-config generators: Create config-specific shader directories
    message(STATUS "Setting up shader symlink")
    
    # Create directories for each configuration
    foreach(CONFIG Debug Release RelWithDebInfo MinSizeRel)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CONFIG})
    endforeach()
    
    # Create custom target to manage shader symlinks
    add_custom_target(setup_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Debug
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Release
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
                ${CMAKE_SOURCE_DIR}/shaders 
                ${CMAKE_BINARY_DIR}/bin/Debug/shaders
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
                ${CMAKE_SOURCE_DIR}/shaders 
                ${CMAKE_BINARY_DIR}/bin/Release/shaders
        COMMENT "Creating shader symlink"
    )
else()
    # Single-config generators: Create shader symlink
    message(STATUS "Setting up shader symlink")
    
    # Create custom target to manage shader symlink
    add_custom_target(setup_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
                ${CMAKE_SOURCE_DIR}/shaders 
                ${CMAKE_BINARY_DIR}/bin/shaders
        COMMENT "Creating shader symlink"
    )
endif()

# Add helpful build information
message(STATUS "========================================")
message(STATUS "OpenGL 4.5 C++20 Project Configuration")  
message(STATUS "========================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if(MSVC)
    message(STATUS "")
    message(STATUS "Windows Build Commands:")
    message(STATUS "  Configure: cmake -G \"Visual Studio 17 2022\" -A x64 -S . -B build")
    message(STATUS "  Build: cmake --build build --config Debug")
    message(STATUS "  Run: build\\bin\\Debug\\OpenGLApp.exe")
else()
    message(STATUS "")
    message(STATUS "Unix Build Commands:")
    message(STATUS "  Configure: cmake -G \"Unix Makefiles\" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -S . -B build")
    message(STATUS "  Build: cmake --build build --parallel")
    message(STATUS "  Run: build/bin/OpenGLApp")
endif()
message(STATUS "========================================")
