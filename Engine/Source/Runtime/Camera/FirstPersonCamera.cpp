#include "hnpch.h"
#include "FirstPersonCamera.h"

#include "Core/Input.h"

namespace Hina
{

void FirstPersonCamera::OnUpdate(const float deltaTime) {
    HN_PROFILE_FUNCTION();

	OnKeyPress(deltaTime);
	OnMouseMove();
}

void FirstPersonCamera::OnEvent(Event &event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FN(FirstPersonCamera::OnMouseScroll));
}

void FirstPersonCamera::FrameAll(const AABB &aabb) {
    m_camera->SetPosition(aabb.GetCentre() + aabb.GetSize());
    m_camera->LookAt(aabb.GetCentre());
}

void FirstPersonCamera::OnKeyPress(const float deltaTime) {
    const float velocity = m_moveSensitive * deltaTime;

    if(Hina::Input::IsKeyPressed(Hina::Key::W)) {
        m_camera->UpdatePosition(velocity * m_camera->GetFront());
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::S)) {
        m_camera->UpdatePosition(-velocity * m_camera->GetFront());
    }

    if(Hina::Input::IsKeyPressed(Hina::Key::A)) {
        m_camera->UpdatePosition(-velocity * m_camera->GetRight());
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::D)) {
        m_camera->UpdatePosition(velocity * m_camera->GetRight());
    }
    
    if(Hina::Input::IsKeyPressed(Hina::Key::Space)) {
        m_camera->UpdatePosition(velocity * Camera::m_worldUp);
    }
    if(Hina::Input::IsKeyPressed(Hina::Key::LeftShift)) {
        m_camera->UpdatePosition(-velocity * Camera::m_worldUp);
    }
}

void FirstPersonCamera::OnMouseMove() {
    HN_PROFILE_FUNCTION();

    static glm::vec2 s_lastPosition = Input::GetMousePosition();
    glm::vec2 crtPosition = Input::GetMousePosition();

    float offset_x = crtPosition.x - s_lastPosition.x;
    float offset_y = s_lastPosition.y - crtPosition.y;

    s_lastPosition = crtPosition;

    m_camera->UpdateYaw(m_rotateSensitive * offset_x);
    m_camera->UpdatePitch(m_rotateSensitive * offset_y);
    m_camera->GetPitch() = std::clamp(m_camera->GetPitch(), glm::degrees(-89.9f), glm::degrees(89.9f));

    m_camera->RecalculateDirections();
}

bool FirstPersonCamera::OnMouseScroll(const MouseScrollEvent &event) {
    const float zoom = m_camera->GetZoom() - m_scrollSensitive * event.GetYOffset();
    m_camera->SetZoom(std::clamp(zoom, glm::radians(5.0f), glm::radians(45.0f)));

    return true;
}

} // namespace Hina
