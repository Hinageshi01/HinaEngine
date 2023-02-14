#include "hnpch.h"
#include "VertexBuffer.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Hina
{

std::unique_ptr<VertexBuffer> VertexBuffer::Create(const uint32_t size, const float *vertices) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLVertexBuffer>(size, vertices);
	
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr;
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
