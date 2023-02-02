#pragma once

namespace Hina
{

enum class ShaderDataType : uint8_t
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

class BufferElement
{
public:
	BufferElement() = delete;
	BufferElement(ShaderDataType type, const std::string &name, bool normalized = false);

	// Returen count of byte of shader data type.
	const uint32_t ShaderDataTypeSize(const ShaderDataType type) const;
	const uint32_t GetComponentCount() const;

	std::string m_name;
	ShaderDataType m_type;
	uint32_t m_size;
	size_t m_offset;
	bool m_normalized;
};

class BufferLayout
{
public:
	BufferLayout() = default;
	BufferLayout(std::initializer_list<BufferElement> elements);

	const uint32_t GetStride() const { return m_stride; }
	const std::vector<BufferElement> &GetElements() const { return m_elements; }
	
	std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
	void CalculateOffsetsAndStride();

	std::vector<BufferElement> m_elements;
	uint32_t m_stride = 0;
};

} // namespace Hina
