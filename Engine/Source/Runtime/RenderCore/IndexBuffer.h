#pragma once

namespace Hina
{

using Index = uint32_t;

class IndexBuffer
{
public:
	static std::shared_ptr<IndexBuffer> Create(const uint32_t size, const Index *indices);

public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual const uint32_t GetCount() const = 0;
};

} // namespace Hina
