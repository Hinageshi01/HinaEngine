#include "hnpch.h"
#include "OpenGLVertexBuffer.h"

#include "RenderCore/BufferLayout.h"

#include <glad/glad.h>

namespace Hina
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const uint32_t size, const float *vertices) {
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	glDeleteBuffers(1, &m_renderID);
}

void OpenGLVertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}

void OpenGLVertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace Hina
