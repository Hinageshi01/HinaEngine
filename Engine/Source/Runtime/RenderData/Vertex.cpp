#include "hnpch.h"
#include "Vertex.h"

namespace Hina
{

BufferLayout Vertex::GetLayOut() {
	return {
		{ ShaderDataType::Float3, "a_position" },
		{ ShaderDataType::Float3, "a_normal" },
		{ ShaderDataType::Float3, "a_tangent" },
		{ ShaderDataType::Float2, "a_textureCoord" },
		{ ShaderDataType::Int4,   "a_bones" },
		{ ShaderDataType::Float4, "a_weights" },
	};
}

} // namespace Hina
