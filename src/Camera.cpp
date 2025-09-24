#include "Camera.h"
#include <algorithm>

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : m_position(0.0f, 0.0f, 3.0f)
    , m_target(0.0f, 0.0f, 0.0f)
    , m_up(0.0f, 1.0f, 0.0f)
    , m_fov(fov)
    , m_aspectRatio(aspectRatio)
    , m_nearPlane(nearPlane)
    , m_farPlane(farPlane)
    , m_viewMatrix(1.0f)
    , m_projectionMatrix(1.0f)
    , m_viewDirty(true)
    , m_projectionDirty(true)
{
}

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
    : m_position(position)
    , m_target(0.0f, 0.0f, 0.0f)
    , m_up(up)
    , m_fov(45.0f)
    , m_aspectRatio(16.0f/9.0f)
    , m_nearPlane(0.1f)
    , m_farPlane(100.0f)
    , m_viewMatrix(1.0f)
    , m_projectionMatrix(1.0f)
    , m_viewDirty(true)
    , m_projectionDirty(true)
{
    // Calculate initial target based on yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_target = m_position + glm::normalize(direction);
}

void Camera::SetPosition(const glm::vec3& position) {
    m_position = position;
    m_viewDirty = true;
}

void Camera::SetTarget(const glm::vec3& target) {
    m_target = target;
    m_viewDirty = true;
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
    m_position = eye;
    m_target = center;
    m_up = up;
    m_viewDirty = true;
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
    m_projectionDirty = true;
}

void Camera::SetAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
    m_projectionDirty = true;
}

void Camera::Translate(const glm::vec3& offset) {
    m_position += offset;
    m_target += offset;
    m_viewDirty = true;
}

void Camera::Rotate(float pitch, float yaw, float roll) {
    // Calculate new direction vector
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    m_target = m_position + glm::normalize(direction);
    
    // Handle roll by rotating the up vector
    if (roll != 0.0f) {
        glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
        m_up = glm::rotate(glm::mat4(1.0f), glm::radians(roll), direction) * glm::vec4(glm::vec3(0, 1, 0), 0.0f);
    }
    
    m_viewDirty = true;
}

void Camera::OrbitAround(const glm::vec3& target, float distance, float pitch, float yaw) {
    m_target = target;
    
    // Convert spherical coordinates to cartesian
    float pitchRad = glm::radians(pitch);
    float yawRad = glm::radians(yaw);
    
    m_position.x = target.x + distance * cos(pitchRad) * sin(yawRad);
    m_position.y = target.y + distance * sin(pitchRad);
    m_position.z = target.z + distance * cos(pitchRad) * cos(yawRad);
    
    m_viewDirty = true;
}

const glm::mat4& Camera::GetViewMatrix() const {
    if (m_viewDirty) {
        UpdateViewMatrix();
        m_viewDirty = false;
    }
    return m_viewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const {
    if (m_projectionDirty) {
        UpdateProjectionMatrix();
        m_projectionDirty = false;
    }
    return m_projectionMatrix;
}

glm::mat4 Camera::GetViewProjectionMatrix() const {
    return GetProjectionMatrix() * GetViewMatrix();
}

void Camera::UpdateViewMatrix() const {
    m_viewMatrix = glm::lookAt(m_position, m_target, m_up);
}

void Camera::UpdateProjectionMatrix() const {
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}
