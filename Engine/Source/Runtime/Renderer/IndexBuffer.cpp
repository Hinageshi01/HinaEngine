#include "hnpch.h"
#include "IndexBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Hina
{

std::unique_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t count, const uint32_t *indices) {
	switch(Renderer::GetAPI()) {
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLIndexBuffer>(count, indices); break;
	
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr; break;
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
