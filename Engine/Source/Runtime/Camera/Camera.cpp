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
    m_moveSensitive = init.m_moveSensitive;
    m_rotateSensitive = init.m_rotateSensitive;
    m_scrollSensitive = init.m_scrollSensitive;

    CalculateDirections();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return glm::perspective(glm::radians(m_zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

glm::mat4 Camera::GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return GetProjectionMatrix(width, height) * GetViewMatrix();
}

void Camera::CalculateDirections() {
    glm::vec3 front = {
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    };

    m_front = glm::normalize(std::move(front));
    m_right = glm::normalize(glm::cross(m_front, s_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

} // namespace Hina
