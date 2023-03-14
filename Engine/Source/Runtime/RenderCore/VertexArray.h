#pragma once

#include "RenderCore/IndexBuffer.h"
#include "RenderCore/VertexBuffer.h"

namespace Hina
{

class VertexArray
{
public:
	static std::shared_ptr<VertexArray> Create();

public:
	virtual ~VertexArray() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;
	virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

	virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
	virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;
};

} // namespace Hina
