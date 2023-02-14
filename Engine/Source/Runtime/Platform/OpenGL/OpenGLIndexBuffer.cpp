#include "hnpch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Hina
{

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t count, const uint32_t *indices) : m_count(count){
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	glDeleteBuffers(1, &m_renderID);
}

void OpenGLIndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}

void OpenGLIndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Hina
