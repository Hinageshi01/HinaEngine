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

private:
	uint32_t m_rendererID = 0;
};

} // namespace Hina
