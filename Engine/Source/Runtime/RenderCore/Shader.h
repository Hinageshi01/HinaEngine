#pragma once

#include <glm/glm.hpp>

namespace Hina
{

class Shader
{
public:
	Shader() = default;
	Shader(const Shader &) = default;
	Shader &operator=(const Shader &) = default;
	Shader(Shader &&) = default;
	Shader &operator=(Shader &&) = default;
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetName(const std::string &name) = 0;
	virtual void SetName(std::string &&name) = 0;
	virtual const std::string &GetName() const = 0;

	virtual void SetInt(const std::string &name, int value) = 0;
	virtual void SetIntArray(const std::string &name, int *values, uint32_t count) = 0;
	virtual void SetFloat(const std::string &name, float value) = 0;
	virtual void SetVec2(const std::string &name, const glm::vec2 &value) = 0;
	virtual void SetVec3(const std::string &name, const glm::vec3 &value) = 0;
	virtual void SetVec4(const std::string &name, const glm::vec4 &value) = 0;
	virtual void SetMat3(const std::string &name, const glm::mat3 &value) = 0;
	virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;

	// TODO : Compute shader.
	static std::shared_ptr<Shader> Create(
		const std::string &name,
		const std::string &vertexShaderPath,
		const std::string &fragmentShaderPath,
		const std::string &geometryShaderPath = "");
};

} // namespace Hina
