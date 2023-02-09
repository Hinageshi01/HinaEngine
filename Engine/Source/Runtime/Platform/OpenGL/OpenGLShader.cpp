#include "hnpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hina
{

namespace
{
constexpr uint32_t LOG_SIZE = 1024;
}

OpenGLShader::OpenGLShader(
	const std::string &name,
	const std::string &vertexShaderPath,
	const std::string &fragmentShaderPath,
	const std::string &geometryShaderPath)
	: m_name(name) {

	std::string vertexCode = std::move(ReadFile(vertexShaderPath));
	std::string fragmentCode = std::move(ReadFile(fragmentShaderPath));
	std::string geometryCode = std::move(ReadFile(geometryShaderPath));
	CreateProgram(vertexCode, fragmentCode, geometryCode);
}

OpenGLShader::~OpenGLShader() {
	glDeleteProgram(m_rendererID);
}

std::string OpenGLShader::ReadFile(const std::string &filepath) {
	if(filepath.empty()) {
		return "";
	}

	std::string result;
	// ifstream closes itself due to RAII
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if(in) {
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if(size != -1) {
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(result.data(), size);
		}
		else {
			HN_CORE_ERROR("Could not read from file '{0}'", filepath);
		}
	}
	else {
		HN_CORE_ERROR("Could not open file '{0}'", filepath);
	}

	return result;
}

void OpenGLShader::CreateProgram(const std::string &vertexCode, const std::string &fragmentCode, const std::string &geometryCode) {
	HN_CORE_INFO("Compiling GLSL shaders");

	const bool useGeometryShader = geometryCode.empty() ? false : true;

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	uint32_t vertexID, fragmentID, geometryID;

	// Vertex shader.
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vShaderCode, NULL);
	glCompileShader(vertexID);
	CheckShaderErrors(vertexID, "VERTEX");

	// Fragment shader.
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fShaderCode, NULL);
	glCompileShader(fragmentID);
	CheckShaderErrors(fragmentID, "FRAGMENT");

	// Geometry shader.
	if(useGeometryShader) {
		const char *gShaderCode = geometryCode.c_str();
		geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryID, 1, &gShaderCode, NULL);
		glCompileShader(geometryID);
		CheckShaderErrors(geometryID, "GEOMETRY");
	}

	// Shader program.
	m_rendererID = glCreateProgram();
	glAttachShader(m_rendererID, vertexID);
	glAttachShader(m_rendererID, fragmentID);
	if(useGeometryShader) {
		glAttachShader(m_rendererID, geometryID);
	}
	glLinkProgram(m_rendererID);
	CheckProgramErrors(m_rendererID, "PROGRAM");

	// Delete the shaders as they're linked into our program now and no longer necessary.
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void OpenGLShader::Bind() const {
	glUseProgram(m_rendererID);
}

void OpenGLShader::Unbind() const {
	glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string &name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count) {
	glUniform1iv(GetUniformLocation(name), count, values);
}

void OpenGLShader::SetFloat(const std::string &name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void OpenGLShader::SetVec2(const std::string &name, const glm::vec2 &value) {
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &value) {
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void OpenGLShader::SetVec4(const std::string &name, const glm::vec4 &value) {
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &value) {
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

const GLint OpenGLShader::GetUniformLocation(const std::string &name) {
	const auto &it = m_uniformNameMap.find(name);
	if(it != m_uniformNameMap.end()) {
		return it->second;
	}
	else {
		m_uniformNameMap[name] = glGetUniformLocation(m_rendererID, name.c_str());
		return m_uniformNameMap[name];
	}
}

void OpenGLShader::CheckShaderErrors(const GLuint shader, const std::string &type) {
	GLint success;
	GLchar infoLog[LOG_SIZE];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
		HN_CORE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {0}", type);
		HN_CORE_ERROR("{0}", infoLog);
	}
}

void OpenGLShader::CheckProgramErrors(const GLuint program, const std::string &type) {
	GLint success;
	GLchar infoLog[LOG_SIZE];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
		HN_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0}", type);
		HN_CORE_ERROR("{0}", infoLog);
	}
}

} // namespace Hina
