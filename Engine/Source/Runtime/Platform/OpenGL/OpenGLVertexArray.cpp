#include "hnpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hina
{

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
	switch(type) {
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3:   return GL_FLOAT;
		case ShaderDataType::Mat4:   return GL_FLOAT;
		case ShaderDataType::Int:    return GL_INT;
		case ShaderDataType::Int2:   return GL_INT;
		case ShaderDataType::Int3:   return GL_INT;
		case ShaderDataType::Int4:   return GL_INT;
		case ShaderDataType::Bool:   return GL_BOOL;
	}

	HN_CORE_ERROR("Unknown ShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
	glCreateVertexArrays(1, &m_rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_rendererID);
}

void OpenGLVertexArray::Bind() const {
	glBindVertexArray(m_rendererID);
}

void OpenGLVertexArray::Unbind() const {
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
	HN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

	glBindVertexArray(m_rendererID);
	vertexBuffer->Bind();

	const auto &layout = vertexBuffer->GetLayout();
	for(const auto &element : layout) {
		switch(element.m_type) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.m_type),
					element.m_normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void *)element.m_offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.m_type),
					layout.GetStride(),
					(const void *)element.m_offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for(uint8_t i = 0; i < count; i++) {
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.m_type),
						element.m_normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void *)(element.m_offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				HN_CORE_ERROR("Unknown ShaderDataType!");
		}
	}

	m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
	glBindVertexArray(m_rendererID);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}


} // namespace Hina
