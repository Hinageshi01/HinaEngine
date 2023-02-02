#pragma once

#include "Renderer/IndexBuffer.h"

namespace Hina
{

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer() = delete;
	OpenGLIndexBuffer(const uint32_t count, uint32_t *indices);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual uint32_t GetCount() const override { return m_count; }

private:
	uint32_t m_rendererID = 0;
	uint32_t m_count = 0;
};

} // namespace Hina
