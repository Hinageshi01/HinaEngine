#include "hnpch.h"
#include "Camera.h"

namespace Hina
{

Camera::Camera(const CameraInitializer &init) {
    Init(init);
}

void Camera::Init(const CameraInitializer &init) {
    m_position = init.m_position;
    m_yaw = init.m_yaw;
    m_pitch = init.m_pitch;
    m_zoom = init.m_zoom;
    m_near = init.m_near;
    m_far = init.m_far;

    RecalculateDirections();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return glm::perspective(m_zoom, static_cast<float>(width) / static_cast<float>(height), m_near, m_far);
}

glm::mat4 Camera::GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return GetProjectionMatrix(width, height) * GetViewMatrix();
}

void Camera::RecalculateDirections() {
    glm::vec3 front = {
        cos(m_yaw) * cos(m_pitch),
        sin(m_pitch),
        sin(m_yaw) * cos(m_pitch)
    };

    m_front = glm::normalize(std::move(front));
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

} // namespace Hina
