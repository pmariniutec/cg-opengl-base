#include "Application.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Application::Application(int width, int height, const char* title)
    : m_window(nullptr), m_width(width), m_height(height), m_title(title), m_shouldClose(false), m_time(0.0f),
      m_firstMouse(true), m_rightMousePressed(false), m_lastX(width / 2.0f), m_lastY(height / 2.0f), m_cameraSpeed(2.5f) {
}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    // Set GLFW error callback
    glfwSetErrorCallback(ErrorCallback);

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Configure GLFW for OpenGL 4.5 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create window
    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    // Set callbacks
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(m_window, MouseCallback);
    glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
    
    // Keep cursor visible by default (Unity-style)

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Print OpenGL information
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set viewport
    glViewport(0, 0, m_width, m_height);

    // Initialize renderer
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->Initialize()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return false;
    }

    // Load shaders
    m_shader = std::make_unique<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");
    m_shader2D = std::make_unique<Shader>("shaders/vertex_2d.glsl", "shaders/fragment_2d.glsl");

    // Initialize camera
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    m_camera->SetAspectRatio((float)m_width / (float)m_height);

    return true;
}

void Application::Run() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(m_window) && !m_shouldClose) {
        // Calculate delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        // Process input
        ProcessInput();

        // Update
        Update(deltaTime);

        // Render
        Render();

        // Swap buffers and poll events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Application::ProcessInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_shouldClose = true;
    }
    
    // Camera movement with WASD only when right mouse button is pressed
    if (m_rightMousePressed) {
        float deltaTime = 0.016f; // Approximate frame time for smooth movement
        float velocity = m_cameraSpeed * deltaTime;
        
        glm::vec3 forward = glm::normalize(m_camera->GetTarget() - m_camera->GetPosition());
        glm::vec3 right = glm::normalize(glm::cross(forward, m_camera->GetUp()));
        
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
            m_camera->SetPosition(m_camera->GetPosition() + forward * velocity);
            m_camera->SetTarget(m_camera->GetTarget() + forward * velocity);
        }
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
            m_camera->SetPosition(m_camera->GetPosition() - forward * velocity);
            m_camera->SetTarget(m_camera->GetTarget() - forward * velocity);
        }
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
            m_camera->SetPosition(m_camera->GetPosition() - right * velocity);
            m_camera->SetTarget(m_camera->GetTarget() - right * velocity);
        }
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
            m_camera->SetPosition(m_camera->GetPosition() + right * velocity);
            m_camera->SetTarget(m_camera->GetTarget() + right * velocity);
        }
    }
}

void Application::Update(float deltaTime) {
    m_time += deltaTime;
}

void Application::Render() {
    // Clear the screen
    m_renderer->Clear(0.1f, 0.1f, 0.15f, 1.0f);

    RenderTestScene();
}

void Application::RenderTestScene() {
    // === 3D CUBE RENDERING ===
    // Set up matrices for 3D rendering
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, m_time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

    // Use 3D Shader
    m_shader->Use();
    
    // Set uniforms
    m_shader->SetMat4("model", model);
    m_shader->SetMat4("view", view);
    m_shader->SetMat4("projection", projection);
    
    // Set lighting uniforms
    m_shader->SetVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    m_shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shader->SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    
    // Draw rotating cube
    m_renderer->DrawCube(1.0f);
    
    // === 2D OVERLAY ELEMENTS ===
    // Switch to 2D shader and identity matrices for 2D overlay elements
    m_shader2D->Use();
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    m_shader2D->SetMat4("model", identity);
    m_shader2D->SetMat4("view", identity);
    m_shader2D->SetMat4("projection", ortho);
    
    // === ANIMATED ELEMENTS (from AnimatedDemo) ===
    // Animated spinning lines in corner
    m_renderer->SetLineWidth(2.0f);
    const int numLines = 8;
    for (int i = 0; i < numLines; ++i) {
        float angle = (2.0f * 3.14159f * i / numLines) + m_time;
        float x1 = -0.7f;
        float y1 = 0.7f;
        float x2 = x1 + 0.15f * cos(angle);
        float y2 = y1 + 0.15f * sin(angle);
        
        m_renderer->DrawLine(x1, y1, 0.0f, x2, y2, 0.0f);
    }
}

void Application::Shutdown() {
    if (m_renderer) {
        m_renderer->Shutdown();
        m_renderer.reset();
    }

    if (m_shader) {
        m_shader->Delete();
        m_shader.reset();
    }

    if (m_shader2D) {
        m_shader2D->Delete();
        m_shader2D.reset();
    }

    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_width = width;
    app->m_height = height;
    glViewport(0, 0, width, height);
    app->m_camera->SetAspectRatio((float)width / (float)height);
}

void Application::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    
    // Only process mouse movement when right mouse button is pressed
    if (!app->m_rightMousePressed) {
        app->m_firstMouse = true; // Reset first mouse when not dragging
        return;
    }
    
    float x = static_cast<float>(xpos);
    float y = static_cast<float>(ypos);
    
    if (app->m_firstMouse) {
        app->m_lastX = x;
        app->m_lastY = y;
        app->m_firstMouse = false;
    }
    
    float xoffset = x - app->m_lastX;
    float yoffset = app->m_lastY - y; // Reversed since y-coordinates go from bottom to top
    app->m_lastX = x;
    app->m_lastY = y;
    
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    // Get current camera vectors
    glm::vec3 position = app->m_camera->GetPosition();
    glm::vec3 target = app->m_camera->GetTarget();
    glm::vec3 up = app->m_camera->GetUp();
    
    // Calculate direction vector
    glm::vec3 direction = glm::normalize(target - position);
    
    // Calculate spherical coordinates
    float yaw = atan2(direction.z, direction.x);
    float pitch = asin(direction.y);
    
    // Update angles
    yaw += glm::radians(xoffset);
    pitch += glm::radians(yoffset);
    
    // Constrain pitch
    if (pitch > glm::radians(89.0f))
        pitch = glm::radians(89.0f);
    if (pitch < glm::radians(-89.0f))
        pitch = glm::radians(-89.0f);
    
    // Calculate new direction vector
    glm::vec3 newDirection;
    newDirection.x = cos(pitch) * cos(yaw);
    newDirection.y = sin(pitch);
    newDirection.z = cos(pitch) * sin(yaw);
    
    // Update camera target
    app->m_camera->SetTarget(position + glm::normalize(newDirection));
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            app->m_rightMousePressed = true;
            app->m_firstMouse = true;
            // Disable cursor when right-clicking (Unity-style)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else if (action == GLFW_RELEASE) {
            app->m_rightMousePressed = false;
            // Re-enable cursor when releasing right-click
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void Application::ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
