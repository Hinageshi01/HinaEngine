#include "hnpch.h"

#include "OpenGLVertexBuffer.h"
#include "Renderer/BufferLayout.h"

#include "glad/glad.h"

namespace Hina
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const uint32_t size, float *vertices) {
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	glDeleteBuffers(1, &m_rendererID);
}

void OpenGLVertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void OpenGLVertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace Hina
