#include "hnpch.h"
#include "BufferLayout.h"

namespace Hina
{

BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized)
	: m_name(name), m_type(type), m_size(ShaderDataTypeSize(type)), m_offset(0), m_normalized(normalized) {}

const uint32_t BufferElement::ShaderDataTypeSize(const ShaderDataType type) const {
	switch(type) {
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
	}

	HN_CORE_ERROR("Unknown ShaderDataType!");
	return 0;
}

const uint32_t BufferElement::GetComponentCount() const {
	switch(m_type) {
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3; // 3 * float3
		case ShaderDataType::Mat4:    return 4; // 4 * float4
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
	}

	HN_CORE_ERROR("Unknown ShaderDataType!");
	return 0;
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : m_elements(elements) {
	CalculateOffsetsAndStride();
}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> &&elements) : m_elements(elements) {
	CalculateOffsetsAndStride();
}

void BufferLayout::CalculateOffsetsAndStride() {
	size_t offset = 0;
	m_stride = 0;
	for(auto &element : m_elements) {
		element.m_offset = offset;
		offset += element.m_size;
		m_stride += element.m_size;
	}
}

} // namespace Hina
