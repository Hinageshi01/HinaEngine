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

	void SetPosition(const glm::vec3 &pos) { m_pCamera->SetPosition(pos); }
	const glm::vec3 &GetPosition() const { return m_pCamera->GetPosition(); }
	glm::vec3 &GetPosition() { return m_pCamera->GetPosition(); }

	void SetYaw(const float yaw) { m_pCamera->SetYaw(yaw); }
	float &GetYaw() { return  m_pCamera->GetYaw(); }
	const float &GetYaw() const { return m_pCamera->GetYaw(); }

	void SetPitch(const float pitch) { m_pCamera->SetPitch(pitch); }
	float &GetPitch() { return m_pCamera->GetPitch(); }
	const float &GetPitch() const { return m_pCamera->GetPitch(); }

	void SetZoom(const float zoom) { m_pCamera->SetZoom(zoom); }
	float &GetZoom() { return m_pCamera->GetZoom(); }
	const float &GetZoom() const { return m_pCamera->GetZoom(); }

	void SetNear(const float _near) { m_pCamera->SetNear(_near); }
	float &GetNear() { return m_pCamera->GetNear(); }
	const float &GetNear() const { return m_pCamera->GetNear(); }

	void SetFar(const float _far) { m_pCamera->SetFar(_far); }
	float &GetFar() { return m_pCamera->GetFar(); }
	const float &GetFar() const { return m_pCamera->GetFar(); }

private:
	bool m_primary = false;
	std::shared_ptr<Camera> m_pCamera;
};

} // namespace Hina
