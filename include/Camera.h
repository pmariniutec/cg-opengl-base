#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(float fov = 45.0f, float aspectRatio = 16.0f/9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch);
    ~Camera() = default;

    // Camera transformations
    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target);
    void LookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up = glm::vec3(0, 1, 0));
    
    // Projection settings
    void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    void SetAspectRatio(float aspectRatio);
    
    // Movement
    void Translate(const glm::vec3& offset);
    void Rotate(float pitch, float yaw, float roll = 0.0f);
    void OrbitAround(const glm::vec3& target, float distance, float pitch, float yaw);
    
    // Matrix getters
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    glm::mat4 GetViewProjectionMatrix() const;
    
    // Getters
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetTarget() const { return m_target; }
    const glm::vec3& GetUp() const { return m_up; }
    float GetFOV() const { return m_fov; }
    
private:
    void UpdateViewMatrix() const;
    void UpdateProjectionMatrix() const;
    
    // Camera parameters
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;
    
    // Projection parameters
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    
    // Matrices
    mutable glm::mat4 m_viewMatrix;
    mutable glm::mat4 m_projectionMatrix;
    mutable bool m_viewDirty;
    mutable bool m_projectionDirty;
};
