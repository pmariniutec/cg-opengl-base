#pragma once

#include <glad/glad.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);
    void DrawTriangle();
    
    // 3D rendering
    void DrawCube(float size = 1.0f);
    void DrawCubeWireframe(float size = 1.0f);
    
    // Point rendering
    void DrawPoint(float x, float y, float z = 0.0f);
    void DrawPoints(const float* vertices, int count);
    
    // Line rendering
    void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2);
    void DrawLines(const float* vertices, int count);
    void DrawLineStrip(const float* vertices, int count);
    void DrawLineLoop(const float* vertices, int count);
    
    // Utility functions
    void SetPointSize(float size);
    void SetLineWidth(float width);
    
    // Shape drawing utilities
    void DrawGrid(int gridSize, float spacing);
    void DrawAxis(float length = 1.0f);
    void DrawCircle(float centerX, float centerY, float radius, int segments = 32);
    
    void Shutdown();

private:
    void SetupTriangle();
    void SetupPointsAndLines();
    void SetupCube();
    
    GLuint m_VAO;  // Vertex Array Object
    GLuint m_VBO;  // Vertex Buffer Object
    
    // VAO/VBO for dynamic point and line rendering
    GLuint m_dynamicVAO;
    GLuint m_dynamicVBO;
    
    // VAO/VBO/EBO for cube rendering
    GLuint m_cubeVAO;
    GLuint m_cubeVBO;
    GLuint m_cubeEBO;
};
