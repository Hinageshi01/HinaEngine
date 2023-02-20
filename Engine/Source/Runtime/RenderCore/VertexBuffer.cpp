#include "hnpch.h"
#include "VertexBuffer.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Hina
{

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const uint32_t size, const float *vertices) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(size, vertices);
	
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::None is currently not supported!");
			return nullptr;
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
}

} // namespace Hina
