#pragma once

#include "Camera/Camera.h"

#include <memory>

namespace Hina
{

class CameraComponent final
{
public:
	CameraComponent(const std::shared_ptr<Camera> &camera) 
		: m_pCamera(camera) {}

	CameraComponent() = default;
	CameraComponent(const CameraComponent &) = default;
	CameraComponent &operator=(const CameraComponent &) = default;
	CameraComponent(CameraComponent &&) = default;
	CameraComponent &operator=(CameraComponent &&) = default;
	~CameraComponent() = default;
	
	bool isPrimary() const { return m_primary; }
	void ActivatePrimary() { m_primary = true; }
	void DeactivatePrimary() { m_primary = false; }

	void SetCamera(const std::shared_ptr<Camera> &camera) { m_pCamera = camera; }

	Camera &GetCamera() { return *m_pCamera; }
	const Camera &GetCamera() const { return *m_pCamera; }

private:
	bool m_primary = false;
	std::shared_ptr<Camera> m_pCamera;
};

} // namespace Hina
