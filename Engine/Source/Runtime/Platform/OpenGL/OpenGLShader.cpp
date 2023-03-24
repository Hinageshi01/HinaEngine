#include "hnpch.h"
#include "OpenGLShader.h"

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
	const std::string &fragmentShaderPath)
	: m_name(name) {
	HN_PROFILE_FUNCTION();

	std::string vertexCode = ReadFile(vertexShaderPath);
	std::string fragmentCode = ReadFile(fragmentShaderPath);
	CreateProgram(vertexCode, fragmentCode);
}

OpenGLShader::~OpenGLShader() {
	glDeleteProgram(m_renderID);
}

void OpenGLShader::Bind() const {
	glUseProgram(m_renderID);
}

void OpenGLShader::Unbind() const {
	glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string &name, int value) {
	HN_PROFILE_FUNCTION();

	glUniform1i(GetUniformLocation(name), value);
}

void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count) {
	HN_PROFILE_FUNCTION();

	glUniform1iv(GetUniformLocation(name), count, values);
}

void OpenGLShader::SetFloat(const std::string &name, float value) {
	HN_PROFILE_FUNCTION();

	glUniform1f(GetUniformLocation(name), value);
}

void OpenGLShader::SetVec2(const std::string &name, const glm::vec2 &value) {
	HN_PROFILE_FUNCTION();

	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &value) {
	HN_PROFILE_FUNCTION();

	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void OpenGLShader::SetVec4(const std::string &name, const glm::vec4 &value) {
	HN_PROFILE_FUNCTION();

	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &value) {
	HN_PROFILE_FUNCTION();

	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
	HN_PROFILE_FUNCTION();

	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

std::string OpenGLShader::ReadFile(const std::string &filepath) {
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if(in) {
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if(size != -1) {
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(result.data(), size);
			in.close();
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

void OpenGLShader::CreateProgram(const std::string &vertexCode, const std::string &fragmentCode) {
	HN_PROFILE_FUNCTION();
	
	HN_CORE_INFO("Compiling GLSL shaders");

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	uint32_t vertexID, fragmentID, geometryID;

	// Vertex shader.
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vShaderCode, NULL);

	{
		HN_PROFILE_SCOPE("void glCompileShader(GLuint shader)");
		glCompileShader(vertexID);
	}

	CheckShaderErrors(vertexID, "VERTEX");

	// Fragment shader.
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fShaderCode, NULL);
	
	{
		HN_PROFILE_SCOPE("void glCompileShader(GLuint shader)");
		glCompileShader(fragmentID);
	}

	CheckShaderErrors(fragmentID, "FRAGMENT");

	// Shader program.
	m_renderID = glCreateProgram();
	glAttachShader(m_renderID, vertexID);
	glAttachShader(m_renderID, fragmentID);
	
	{
		HN_PROFILE_SCOPE("void glLinkProgram(GLuint program)");
		glLinkProgram(m_renderID);
	}

	CheckProgramErrors(m_renderID, "PROGRAM");

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

const GLint OpenGLShader::GetUniformLocation(const std::string &name) {
	const auto &it = m_uniformNameMap.find(name);
	if(it != m_uniformNameMap.end()) {
		return it->second;
	}
	else {
		m_uniformNameMap[name] = glGetUniformLocation(m_renderID, name.c_str());
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
