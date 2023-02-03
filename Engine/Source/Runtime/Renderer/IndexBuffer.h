#pragma once

namespace Hina
{

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual uint32_t GetCount() const = 0;

	static std::unique_ptr<IndexBuffer> Create(const uint32_t count, uint32_t *indices);
};

} // namespace Hina
