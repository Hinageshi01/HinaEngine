#pragma once

#include "Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Hina
{

class OpenGLShader : public Shader
{
public:
	OpenGLShader(
		const std::string &name,
		const std::string &vertexShaderPath,
		const std::string &fragmentShaderPath,
		const std::string &geometryShaderPath = "");
	
	virtual ~OpenGLShader();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void SetName(const std::string &name) override { m_name = name; };
	virtual const std::string &GetName() const override { return m_name; }

	virtual void SetInt(const std::string &name, int value) override;
	virtual void SetIntArray(const std::string &name, int *values, uint32_t count) override;
	virtual void SetFloat(const std::string &name, float value) override;
	virtual void SetVec2(const std::string &name, const glm::vec2 &value) override;
	virtual void SetVec3(const std::string &name, const glm::vec3 &value) override;
	virtual void SetVec4(const std::string &name, const glm::vec4 &value) override;
	virtual void SetMat3(const std::string &name, const glm::mat3 &value) override;
	virtual void SetMat4(const std::string &name, const glm::mat4 &value) override;

private:
	std::string ReadFile(const std::string &filepath);

	void CreateProgram(const std::string &vertexCode, const std::string &fragmentCode, const std::string &geometryCode = "");

	// Also add new pair if name not exist.
	const GLint GetUniformLocation(const std::string &name);
	
	void CheckShaderErrors(const GLuint shader, const std::string &type);
	void CheckProgramErrors(const GLuint program, const std::string &type);

	uint32_t m_rendererID;
	std::string m_name;
	std::unordered_map<std::string, GLint> m_uniformNameMap;
};

} // namespace Hina
