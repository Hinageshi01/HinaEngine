#pragma once

#include "Camera/CameraController.h"
#include "Event/MouseEvent.h"
#include "RenderData/AABB.h"

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

	void FrameAll(const AABB &aabb);

	virtual void SetCamera(const std::shared_ptr<Camera> &pCamera) override { m_camera = pCamera; }
	Camera &GetCamera() { return *m_camera; }
	const Camera &GetCamera() const { return *m_camera; }

	void SetSpeed(const float speed) { m_moveSensitive = speed; }
	float GetSpeed() { return m_moveSensitive; }
	const float GetSpeed() const { return m_moveSensitive; }

private:
	void OnKeyPress(const float deltaTime);
	void OnMouseMove();
	bool OnMouseScroll(const MouseScrollEvent &event);

	std::shared_ptr<Camera> m_camera;

	float m_moveSensitive = 2.5f;
	float m_rotateSensitive = 0.002f;
	float m_scrollSensitive = 1.0f;
};

} // namespace Hina
