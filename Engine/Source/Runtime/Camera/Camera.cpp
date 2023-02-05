#include "hnpch.h"
#include "Camera.h"

namespace Hina
{

Camera::Camera(const CameraInitializer &init) {
    Init(init);
}

void Camera::Init(const CameraInitializer &init) {
    m_position = init.m_position;
    m_worldUp = init.m_worldUp;
    m_yaw = init.m_yaw;
    m_pitch = init.m_pitch;
    m_zoom = init.m_zoom;
    m_speed = init.m_speed;
    m_sensitivity = init.m_sensitivity;

    Update();
}

const glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

const glm::mat4 Camera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return glm::perspective(glm::radians(m_zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

const glm::mat4 Camera::GetViewProjectionMatrix(const uint32_t width, const uint32_t height) const {
    return GetProjectionMatrix(width, height) * GetViewMatrix();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = m_speed * deltaTime;
    if(direction == CameraMovement::FORWARD)
        m_position += m_front * velocity;
    if(direction == CameraMovement::BACKWARD)
        m_position -= m_front * velocity;
    if(direction == CameraMovement::LEFT)
        m_position -= m_right * velocity;
    if(direction == CameraMovement::RIGHT)
        m_position += m_right * velocity;
    if(direction == CameraMovement::UP)
        m_position += m_up * velocity;
    if(direction == CameraMovement::DOWN)
        m_position -= m_up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    m_pitch = std::clamp(m_pitch, -89.9f, 89.9f);

    Update();
}

void Camera::ProcessMouseScroll(float yoffset) {
    m_zoom -= (float)yoffset;
    if(m_zoom < 1.0f)
        m_zoom = 1.0f;
    if(m_zoom > 45.0f)
        m_zoom = 45.0f;
}

void Camera::Update() {
    glm::vec3 front = {
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    };

    m_front = std::move(glm::normalize(front));
    m_right = std::move(glm::normalize(glm::cross(m_front, m_worldUp)));
    m_up = std::move(glm::normalize(glm::cross(m_right, m_front)));
}

} // namespace Hina
