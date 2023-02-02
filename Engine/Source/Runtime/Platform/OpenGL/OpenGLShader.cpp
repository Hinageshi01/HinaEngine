#include "hnpch.h"

#include "OpenGLShader.h"

namespace Hina
{

OpenGLShader::OpenGLShader(const std::string &vertexCode, const std::string &fragmentCode, const std::string &geometryCode) {
    HN_CORE_INFO("Compiling GLSL shaders");

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    uint32_t vertex, fragment;

    // Vertex shader.
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // Fragment shader.
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    
    // Geometry shader.
    if(!geometryCode.empty()) {
        const char *gShaderCode = geometryCode.c_str();
        uint32_t geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }

    // Shader program.
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);
    CheckCompileErrors(m_program, "PROGRAM");
    
    // Delete the shaders as they're linked into our program now and no longer necessary.
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}
void OpenGLShader::Bind() const {
    glUseProgram(m_program);
}

void OpenGLShader::Unbind() const {
    glUseProgram(0);
}

void OpenGLShader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), static_cast<GLint>(value));
}
void OpenGLShader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}
void OpenGLShader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}
void OpenGLShader::SetVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void OpenGLShader::SetVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);
}
void OpenGLShader::SetVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void OpenGLShader::SetVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);
}
void OpenGLShader::SetVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void OpenGLShader::SetVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);
}
void OpenGLShader::SetMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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

}// namespace Hina
