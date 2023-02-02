#pragma once

#include "Renderer/VertexBuffer.h"

namespace Hina
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer() = delete;
	OpenGLVertexBuffer(const uint32_t size, float *vertices);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual const BufferLayout &GetLayout() const override { return m_Layout; }
	virtual void SetLayout(BufferLayout layout) override { m_Layout = std::move(layout); }

private:
	uint32_t m_rendererID = 0;
	BufferLayout m_Layout;
};

} // namespace Hina
