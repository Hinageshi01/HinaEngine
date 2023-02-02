#include "hnpch.h"

#include "IndexBuffer.h"

namespace Hina
{

std::unique_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {
	// switch(RendererAPI::GetAPI()) {
	// 	case RendererAPI::API::OpenGL:
	// 		return ; break;
	// 
	// 	case RendererAPI::API::None:
	// 		HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
	// 		return nullptr; break;
	// }

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
