#pragma once

#include <glm/glm.hpp>

namespace Hina
{

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	// TODO : Provide a overload function with r value parameter.
	virtual void SetInt(const std::string &name, int value) = 0;
	virtual void SetIntArray(const std::string &name, int *values, uint32_t count) = 0;
	virtual void SetFloat(const std::string &name, float value) = 0;
	virtual void SetVec2(const std::string &name, const glm::vec2 &value) = 0;
	virtual void SetVec3(const std::string &name, const glm::vec3 &value) = 0;
	virtual void SetVec4(const std::string &name, const glm::vec4 &value) = 0;
	virtual void SetMat3(const std::string &name, const glm::mat3 &value) = 0;
	virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;

	virtual const std::string &GetName() const = 0;

	static std::shared_ptr<Shader> Create(
		const std::string &name,
		const std::string &vertexShaderPath,
		const std::string &fragmentShaderPath,
		const std::string &geometryShaderPath = "");
};

} // namespace Hina
