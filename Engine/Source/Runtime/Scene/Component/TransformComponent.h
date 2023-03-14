#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Hina
{

class TransformComponent final
{
public:
	TransformComponent(const glm::vec3 &translation)
		: m_translation(translation) {}

	TransformComponent() = default;
	TransformComponent &operator=(const TransformComponent &) = default;
	TransformComponent(const TransformComponent &) = default;
	TransformComponent &operator=(TransformComponent &&) = default;
	TransformComponent(TransformComponent &&) = default;
	~TransformComponent() = default;

	void SetTranslation(const glm::vec3 &translation) { m_translation = translation; }
	glm::vec3 &GetTranslation() { return m_translation; }
	const glm::vec3 &GetTranslation() const { return m_translation; }

	void SetRotation(const glm::vec3 &rotation) { m_rotation = rotation; }
	glm::vec3 &GetRotation() { return m_rotation; }
	const glm::vec3 &GetRotation() const { return m_rotation; }

	void SetScale(const glm::vec3 &scale) { m_scale = scale; }
	glm::vec3 &GetScale() { return m_scale; }
	const glm::vec3 &GetScale() const { return m_scale; }

	glm::mat4 GetTransform() const {
		glm::mat4 quat = glm::toMat4(glm::quat(m_rotation));

		return glm::translate(glm::mat4(1.0f), m_translation)
			* std::move(quat) * glm::scale(glm::mat4(1.0f), m_scale);
	}

private:
	glm::vec3 m_translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };
};

} // namespace Hina
