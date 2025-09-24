#include "Renderer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <cmath>

Renderer::Renderer() : m_VAO(0), m_VBO(0), m_dynamicVAO(0), m_dynamicVBO(0), m_cubeVAO(0), m_cubeVBO(0), m_cubeEBO(0) {
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize() {
    SetupTriangle();
    SetupPointsAndLines();
    SetupCube();
    return true;
}

void Renderer::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawTriangle() {
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::DrawCube(float size) {
    glBindVertexArray(m_cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::DrawCubeWireframe(float size) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    DrawCube(size);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::Shutdown() {
    if (m_VBO != 0) {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
    if (m_dynamicVBO != 0) {
        glDeleteBuffers(1, &m_dynamicVBO);
        m_dynamicVBO = 0;
    }
    if (m_dynamicVAO != 0) {
        glDeleteVertexArrays(1, &m_dynamicVAO);
        m_dynamicVAO = 0;
    }
    if (m_cubeVBO != 0) {
        glDeleteBuffers(1, &m_cubeVBO);
        m_cubeVBO = 0;
    }
    if (m_cubeEBO != 0) {
        glDeleteBuffers(1, &m_cubeEBO);
        m_cubeEBO = 0;
    }
    if (m_cubeVAO != 0) {
        glDeleteVertexArrays(1, &m_cubeVAO);
        m_cubeVAO = 0;
    }
}

void Renderer::SetupTriangle() {
    // Triangle vertices
    float vertices[] = {
        // positions      // colors
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom left
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // top
    };

    // Generate and bind VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Generate and bind VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

void Renderer::SetupPointsAndLines() {
    // Generate and bind dynamic VAO for points and lines
    glGenVertexArrays(1, &m_dynamicVAO);
    glBindVertexArray(m_dynamicVAO);

    // Generate and bind dynamic VBO
    glGenBuffers(1, &m_dynamicVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);

    // Position attribute (location = 0) - same as triangle setup
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1) - same as triangle setup
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

// Point rendering functions
void Renderer::DrawPoint(float x, float y, float z) {
    float vertices[] = {
        x, y, z, 1.0f, 1.0f, 1.0f  // White point
    };
    DrawPoints(vertices, 1);
}

void Renderer::DrawPoints(const float* vertices, int count) {
    glBindVertexArray(m_dynamicVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
    glBufferData(GL_ARRAY_BUFFER, count * 6 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_POINTS, 0, count);
    
    glBindVertexArray(0);
}

// Line rendering functions
void Renderer::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2) {
    float vertices[] = {
        x1, y1, z1, 1.0f, 1.0f, 1.0f,  // First point - white
        x2, y2, z2, 1.0f, 1.0f, 1.0f   // Second point - white
    };
    DrawLines(vertices, 1);
}

void Renderer::DrawLines(const float* vertices, int count) {
    glBindVertexArray(m_dynamicVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
    glBufferData(GL_ARRAY_BUFFER, count * 2 * 6 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_LINES, 0, count * 2);
    
    glBindVertexArray(0);
}

void Renderer::DrawLineStrip(const float* vertices, int count) {
    glBindVertexArray(m_dynamicVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
    glBufferData(GL_ARRAY_BUFFER, count * 6 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_LINE_STRIP, 0, count);
    
    glBindVertexArray(0);
}

void Renderer::DrawLineLoop(const float* vertices, int count) {
    glBindVertexArray(m_dynamicVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
    glBufferData(GL_ARRAY_BUFFER, count * 6 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_LINE_LOOP, 0, count);
    
    glBindVertexArray(0);
}

// Utility functions
void Renderer::SetPointSize(float size) {
    glPointSize(size);
}

void Renderer::SetLineWidth(float width) {
    glLineWidth(width);
}

// Shape drawing utilities
void Renderer::DrawGrid(int gridSize, float spacing) {
    std::vector<float> vertices;
    
    float halfSize = (gridSize * spacing) * 0.5f;
    
    // Vertical lines
    for (int i = 0; i <= gridSize; ++i) {
        float x = -halfSize + i * spacing;
        vertices.insert(vertices.end(), {
            x, -halfSize, 0.0f,  0.5f, 0.5f, 0.5f,  // Bottom
            x,  halfSize, 0.0f,  0.5f, 0.5f, 0.5f   // Top
        });
    }
    
    // Horizontal lines
    for (int i = 0; i <= gridSize; ++i) {
        float y = -halfSize + i * spacing;
        vertices.insert(vertices.end(), {
            -halfSize, y, 0.0f,  0.5f, 0.5f, 0.5f,  // Left
             halfSize, y, 0.0f,  0.5f, 0.5f, 0.5f   // Right
        });
    }
    
    DrawLines(vertices.data(), (gridSize + 1) * 2);
}

void Renderer::DrawAxis(float length) {
    float vertices[] = {
        // X-axis (Red)
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        // Y-axis (Green)
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, length, 0.0f,  0.0f, 1.0f, 0.0f,
        // Z-axis (Blue)
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, length,  0.0f, 0.0f, 1.0f
    };
    
    DrawLines(vertices, 3);
}

void Renderer::DrawCircle(float centerX, float centerY, float radius, int segments) {
    std::vector<float> vertices;
    
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.14159f * i / segments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        
        vertices.insert(vertices.end(), {
            x, y, 0.0f,  1.0f, 1.0f, 0.0f  // Yellow circle
        });
    }
    
    DrawLineLoop(vertices.data(), segments + 1);
}

void Renderer::SetupCube() {
    // Cube vertices with positions and normals
    float cubeVertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 0
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 1
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 2
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 3
        
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 4
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 5
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 6
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 7
        
        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 8
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 9
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 10
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 11
        
        // Right face
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 12
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 13
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 14
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 15
        
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 16
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 17
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 18
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 19
        
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 20
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 21
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, // 22
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f  // 23
    };
    
    unsigned int cubeIndices[] = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 6, 5, 6, 4, 7,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 14, 13, 14, 12, 15,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 22, 21, 22, 20, 23
    };
    
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_cubeVBO);
    glGenBuffers(1, &m_cubeEBO);
    
    glBindVertexArray(m_cubeVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
    
    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Normal attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}
