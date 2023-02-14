#include "hnpch.h"
#include "IndexBuffer.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Hina
{

std::unique_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t count, const uint32_t *indices) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLIndexBuffer>(count, indices);
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
