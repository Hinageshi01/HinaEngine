#pragma once

#include "Camera/Camera.h"
#include "Event/MouseEvent.h"

namespace Hina
{

class FirstPersonCamera
{
public:
	void OnUpdate(const float deltaTime);
	void OnEvent(Event &event);

	Camera &GetCamera() { return m_camera; }
	const Camera &GetCamera() const { return m_camera; }

private:
	void OnKeyPress(const float deltaTime);
	void OnMouseMove();
	bool OnMouseScroll(MouseScrolledEvent &event);

	Camera m_camera;
};

} // namespace Hina
