#pragma once

#include "Renderer/BufferLayout.h"

namespace Hina
{

class VertexBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual const BufferLayout &GetLayout() const = 0;
	virtual void SetLayout(BufferLayout layout) = 0;

	static std::unique_ptr<VertexBuffer> Create(const uint32_t size, const float *vertices);
};

} // namespace Hina
