#pragma once

namespace Hina
{

class IndexBuffer
{
public:
	static std::shared_ptr<IndexBuffer> Create(const uint32_t count, const uint32_t *indices);

public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual const uint32_t GetCount() const = 0;
};

} // namespace Hina
