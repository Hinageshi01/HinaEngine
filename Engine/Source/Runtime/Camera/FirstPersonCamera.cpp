#include "hnpch.h"
#include "FirstPersonCamera.h"

namespace Hina
{

void FirstPersonCamera::OnUpdate(const float deltaTime) {
	OnKeyPress(deltaTime);
	OnMouseMove();
}

void FirstPersonCamera::OnEvent(Event &event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FN(FirstPersonCamera::OnMouseScroll));
}

void FirstPersonCamera::OnKeyPress(const float deltaTime) {
    const float velocity = m_camera.m_moveSensitive * deltaTime;

    if(Hina::Input::IsKeyPressed(Hina::Key::W)) {
        m_camera.m_position += m_camera.m_front * velocity;
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::S)) {
        m_camera.m_position -= m_camera.m_front * velocity;
    }

    if(Hina::Input::IsKeyPressed(Hina::Key::A)) {
        m_camera.m_position -= m_camera.m_right * velocity;
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::D)) {
        m_camera.m_position += m_camera.m_right * velocity;
    }
    
    if(Hina::Input::IsKeyPressed(Hina::Key::Space)) {
        m_camera.m_position += m_camera.m_worldUp * velocity;
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::LeftShift)) {
        m_camera.m_position -= m_camera.m_worldUp * velocity;
    }
}

void FirstPersonCamera::OnMouseMove() {
    static glm::vec2 lastPosition = Input::GetMousePosition();
    glm::vec2 crtPosition = Input::GetMousePosition();

    float offset_x = crtPosition.x - lastPosition.x;
    float offset_y = lastPosition.y - crtPosition.y;

    lastPosition = crtPosition;

    m_camera.m_yaw += offset_x * m_camera.m_rotateSensitive;
    m_camera.m_pitch += offset_y * m_camera.m_rotateSensitive;
    m_camera.m_pitch = std::clamp(m_camera.m_pitch, -89.9f, 89.9f);

    m_camera.CalculateDirections();
}

bool FirstPersonCamera::OnMouseScroll(MouseScrollEvent &event) {
    m_camera.m_zoom -= event.GetYOffset() * m_camera.m_scrollSensitive;
    m_camera.m_zoom = std::clamp(m_camera.m_zoom, 1.0f, 45.0f);

    return true;
}

} // namespace Hina
