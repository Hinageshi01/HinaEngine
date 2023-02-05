#include "hnpch.h"

#include "Renderer/Renderer.h"
#include "VertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Hina
{

std::unique_ptr<VertexBuffer> VertexBuffer::Create(const uint32_t size, const float *vertices) {
	switch(Renderer::GetAPI()) {
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLVertexBuffer>(size, vertices); break;
	
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr; break;
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
