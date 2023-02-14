#pragma once

#include "Camera/Camera.h"
#include "Event/MouseEvent.h"

namespace Hina
{

class FirstPersonCamera final
{
public:
	FirstPersonCamera() = default;
	FirstPersonCamera(const FirstPersonCamera &) = default;
	FirstPersonCamera &operator=(const FirstPersonCamera &) = default;
	FirstPersonCamera(FirstPersonCamera &&) = default;
	FirstPersonCamera &operator=(FirstPersonCamera &&) = default;
	~FirstPersonCamera() = default;

	void OnUpdate(const float deltaTime);
	void OnEvent(Event &event);

	Camera &GetCamera() { return m_camera; }
	const Camera &GetCamera() const { return m_camera; }

private:
	void OnKeyPress(const float deltaTime);
	void OnMouseMove();
	bool OnMouseScroll(MouseScrollEvent &event);

	Camera m_camera;
};

} // namespace Hina
