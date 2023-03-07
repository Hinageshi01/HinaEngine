#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Hina
{

struct NameComponent
{
	NameComponent(std::string _name) : name(_name) {}

	NameComponent() = default;
	NameComponent &operator=(const NameComponent &) = default;
	NameComponent(const NameComponent &) = default;
	NameComponent &operator=(NameComponent &&) = default;
	NameComponent(NameComponent &&) = default;
	~NameComponent() = default;

	std::string name;
};

struct TransformComponent
{
	TransformComponent(const glm::vec3 &_translation)
		: translation(translation) {}

	TransformComponent() = default;
	TransformComponent &operator=(const TransformComponent &) = default;
	TransformComponent(const TransformComponent &) = default;
	TransformComponent &operator=(TransformComponent &&) = default;
	TransformComponent(TransformComponent &&) = default;
	~TransformComponent() = default;

	glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 GetTransform() const {
		glm::mat4 quat = glm::toMat4(glm::quat(rotation));

		return glm::translate(glm::mat4(1.0f), translation)
			* quat * glm::scale(glm::mat4(1.0f), scale);
	}
};

} // namespace Hina
