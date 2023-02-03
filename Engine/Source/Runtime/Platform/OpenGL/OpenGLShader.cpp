#include "hnpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hina
{

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
	CheckCompileErrors(vertexID, "VERTEX");

	// Fragment shader.
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fShaderCode, NULL);
	glCompileShader(fragmentID);
	CheckCompileErrors(fragmentID, "FRAGMENT");

	// Geometry shader.
	if(useGeometryShader) {
		const char *gShaderCode = geometryCode.c_str();
		geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryID, 1, &gShaderCode, NULL);
		glCompileShader(geometryID);
		CheckCompileErrors(geometryID, "GEOMETRY");
	}

	// Shader program.
	m_rendererID = glCreateProgram();
	glAttachShader(m_rendererID, vertexID);
	glAttachShader(m_rendererID, fragmentID);
	if(useGeometryShader) {
		glAttachShader(m_rendererID, geometryID);
	}
	glLinkProgram(m_rendererID);
	CheckCompileErrors(m_rendererID, "PROGRAM");

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
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform1i(location, value);
}

void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform1iv(location, count, values);
}

void OpenGLShader::SetFloat(const std::string &name, float value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform1f(location, value);
}

void OpenGLShader::SetVec2(const std::string &name, const glm::vec2 &value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::SetVec4(const std::string &name, const glm::vec4 &value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
	GLint location = glGetUniformLocation(m_rendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::CheckCompileErrors(const GLuint shader, const std::string &type) {
	GLint success;
	GLchar infoLog[1024];

	if(type != "PROGRAM") {
		// Shaders compile error.
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			HN_CORE_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {0}", type);
			HN_CORE_ERROR("{0}", infoLog);
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			HN_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0}", type);
			HN_CORE_ERROR("{0}", infoLog);
		}
	}
}

} // namespace Hina
