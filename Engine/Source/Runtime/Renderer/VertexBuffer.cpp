#include "hnpch.h"

#include "Renderer/RendererAPI.h"
#include "VertexBuffer.h"

namespace Hina
{

std::unique_ptr<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
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
