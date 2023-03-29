#pragma once

#include "RenderCore/VertexBuffer.h"

namespace Hina
{

class OpenGLVertexBuffer final : public VertexBuffer
{
public:
	OpenGLVertexBuffer(const size_t size, const float *vertices);

	OpenGLVertexBuffer() = delete;
	OpenGLVertexBuffer(const OpenGLVertexBuffer &) = default;
	OpenGLVertexBuffer &operator=(const OpenGLVertexBuffer &) = default;
	OpenGLVertexBuffer(OpenGLVertexBuffer &&) = default;
	OpenGLVertexBuffer &operator=(OpenGLVertexBuffer &&) = default;
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual const BufferLayout &GetLayout() const override { return m_layout; }
	virtual void SetLayout(const BufferLayout &layout) override { m_layout = layout; }
	virtual void SetLayout(BufferLayout &&layout) override { m_layout = std::move(layout); }

private:
	uint32_t m_renderID = 0;
	BufferLayout m_layout;
};

} // namespace Hina
