# Source files
add_executable(OpenGLApp
    main.cpp
    Application.cpp
    Shader.cpp
    Renderer.cpp
    Camera.cpp
)

target_include_directories(OpenGLApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glm
)

target_link_libraries(OpenGLApp PRIVATE
    glfw
    glad
    glm::glm
    OpenGL::GL
)

# Set startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenGLApp)
