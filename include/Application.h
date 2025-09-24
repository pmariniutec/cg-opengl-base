#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

class Renderer;
class Shader;
class Camera;

class Application {
public:
    Application(int width = 800, int height = 600, const char* title = "OpenGL 4.5 Application");
    ~Application();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    
    // Combined demo rendering method
    void RenderTestScene();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void ErrorCallback(int error, const char* description);

    GLFWwindow* m_window;
    int m_width, m_height;
    const char* m_title;
    
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Shader> m_shader2D;
    std::unique_ptr<Camera> m_camera;
    
    bool m_shouldClose;
    float m_time;  // For animations
    
    // Camera control variables
    bool m_firstMouse;
    bool m_rightMousePressed;
    float m_lastX, m_lastY;
    float m_cameraSpeed;
};
