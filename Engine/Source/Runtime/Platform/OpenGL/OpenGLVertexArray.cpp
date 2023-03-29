#include "hnpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hina
{

namespace Utils
{

const std::unordered_map<ShaderDataType, GLenum> shaderDataTypeToOpenGLBaseType = {
	{ ShaderDataType::Float,  GL_FLOAT },
	{ ShaderDataType::Float2, GL_FLOAT },
	{ ShaderDataType::Float3, GL_FLOAT },
	{ ShaderDataType::Float4, GL_FLOAT },
	{ ShaderDataType::Mat3,   GL_FLOAT },
	{ ShaderDataType::Mat4,   GL_FLOAT },
	{ ShaderDataType::Int,    GL_INT },
	{ ShaderDataType::Int2,   GL_INT },
	{ ShaderDataType::Int3,   GL_INT },
	{ ShaderDataType::Int4,   GL_INT },
	{ ShaderDataType::Bool,   GL_BOOL },
};

} // namespace Utils

OpenGLVertexArray::OpenGLVertexArray() {
	glCreateVertexArrays(1, &m_renderID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_renderID);
}

void OpenGLVertexArray::Bind() const {
	glBindVertexArray(m_renderID);
}

void OpenGLVertexArray::Unbind() const {
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
	HN_PROFILE_FUNCTION();

	if(vertexBuffer->GetLayout().GetElements().empty()) {
		HN_CORE_ERROR("Vertex Buffer has no layout!");
		return;
	}

	glBindVertexArray(m_renderID);
	vertexBuffer->Bind();

	const auto &layout = vertexBuffer->GetLayout();
	for(const auto &element : layout) {
		switch(element.m_type) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribPointer(
					m_vertexBufferIndex,
					element.GetComponentCount(),
					Utils::shaderDataTypeToOpenGLBaseType.at(element.m_type),
					element.m_normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void *)element.m_offset);
				++m_vertexBufferIndex;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribIPointer(
					m_vertexBufferIndex,
					element.GetComponentCount(),
					Utils::shaderDataTypeToOpenGLBaseType.at(element.m_type),
					layout.GetStride(),
					(const void *)element.m_offset);
				++m_vertexBufferIndex;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for(uint8_t i = 0; i < count; i++) {
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribPointer(
						m_vertexBufferIndex,
						count,
						Utils::shaderDataTypeToOpenGLBaseType.at(element.m_type),
						element.m_normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void *)(element.m_offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_vertexBufferIndex, 1);
					++m_vertexBufferIndex;
				}
				break;
			}
			default:
				HN_CORE_ERROR("Unknown ShaderDataType!");
		}
	}

	m_vertexBuffers.push_back(vertexBuffer);

	glBindVertexArray(0);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
	glBindVertexArray(m_renderID);
	indexBuffer->Bind();
	m_indexBuffer = indexBuffer;
	glBindVertexArray(0);
}

} // namespace Hina
