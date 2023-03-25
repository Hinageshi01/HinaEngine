#pragma once

#include "RenderCore/IndexBuffer.h"

namespace Hina
{

class OpenGLIndexBuffer final : public IndexBuffer
{
public:
	OpenGLIndexBuffer(const uint32_t size, const uint32_t *indices);

	OpenGLIndexBuffer() = delete;
	OpenGLIndexBuffer(const OpenGLIndexBuffer &) = default;
	OpenGLIndexBuffer &operator=(const OpenGLIndexBuffer &) = default;
	OpenGLIndexBuffer(OpenGLIndexBuffer &&) = default;
	OpenGLIndexBuffer &operator=(OpenGLIndexBuffer &&) = default;
	~OpenGLIndexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual const uint32_t GetCount() const override { return m_count; }

private:
	uint32_t m_renderID = 0;
	// Count of uint32_t as the index type will always be uint32_t.
	uint32_t m_count = 0;
};

} // namespace Hina
