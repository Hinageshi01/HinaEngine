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
    m_moveSensitive = init.m_moveSensitive;
    m_rotateSensitive = init.m_rotateSensitive;
    m_scrollSensitive = init.m_scrollSensitive;

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

void Camera::OnKeyPress(const float deltaTime) {
    if(Hina::Input::IsKeyPressed(Hina::Key::W)) {
        ProcessKeyPress(Hina::CameraMovement::FORWARD, deltaTime);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::A)) {
        ProcessKeyPress(Hina::CameraMovement::LEFT, deltaTime);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::S)) {
        ProcessKeyPress(Hina::CameraMovement::BACKWARD, deltaTime);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::D)) {
        ProcessKeyPress(Hina::CameraMovement::RIGHT, deltaTime);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::Space)) {
        ProcessKeyPress(Hina::CameraMovement::UP, deltaTime);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::LeftShift)) {
        ProcessKeyPress(Hina::CameraMovement::DOWN, deltaTime);
    }
}

void Camera::OnMouseMove() {
    static glm::vec2 lastPosition = Input::GetMousePosition();
    glm::vec2 crtPosition = Input::GetMousePosition();

    float offset_x = crtPosition.x - lastPosition.x;
    float offset_y = lastPosition.y - crtPosition.y;

    lastPosition = crtPosition;

    ProcessMouseMove(offset_x, offset_y);
}

bool Camera::OnMouseScroll(MouseScrolledEvent &event) {
    ProcessMouseScroll(event.GetYOffset());

    return true;
}

void Camera::ProcessKeyPress(const CameraMovement direction, const float deltaTime) {
    float velocity = m_moveSensitive * deltaTime;

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

void Camera::ProcessMouseMove(float offset_x, float offset_y) {
    m_yaw += offset_x * m_rotateSensitive;
    m_pitch += offset_y * m_rotateSensitive;
    m_pitch = std::clamp(m_pitch, -89.9f, 89.9f);

    Update();
}

void Camera::ProcessMouseScroll(float offset_y) {
    m_zoom -= offset_y * m_scrollSensitive;
    if(m_zoom < 1.0f) {
        m_zoom = 1.0f;
    }
    if(m_zoom > 45.0f) {
        m_zoom = 45.0f;
    }
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
