#pragma once

#include "RenderCore/VertexArray.h"

namespace Hina
{

class OpenGLVertexArray final : public VertexArray
{
public:
	OpenGLVertexArray();
	OpenGLVertexArray(const OpenGLVertexArray &) = default;
	OpenGLVertexArray &operator=(const OpenGLVertexArray &) = default;
	OpenGLVertexArray(OpenGLVertexArray &&) = default;
	OpenGLVertexArray &operator=(OpenGLVertexArray &&) = default;
	virtual ~OpenGLVertexArray();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
	virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

	virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const { return m_vertexBuffers; }
	virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const { return m_indexBuffer; }

private:
	uint32_t m_renderID;
	uint32_t m_vertexBufferIndex = 0;

	std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} // namespace Hina
