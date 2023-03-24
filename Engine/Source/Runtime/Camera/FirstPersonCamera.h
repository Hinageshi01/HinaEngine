#pragma once

#include "Camera/CameraController.h"
#include "Event/MouseEvent.h"

namespace Hina
{

class FirstPersonCamera : CameraController
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

	virtual void SetCamera(const std::shared_ptr<Camera> &pCamera) override { m_camera = pCamera; }
	Camera &GetCamera() { return *m_camera; }
	const Camera &GetCamera() const { return *m_camera; }

private:
	void OnKeyPress(const float deltaTime);
	void OnMouseMove();
	bool OnMouseScroll(const MouseScrollEvent &event);

	std::shared_ptr<Camera> m_camera;

	const float m_moveSensitive = 2.5f;
	const float m_rotateSensitive = 0.002f;
	const float m_scrollSensitive = 1.0f;
};

} // namespace Hina
