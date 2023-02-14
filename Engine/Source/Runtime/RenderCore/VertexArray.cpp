#include "hnpch.h"
#include "VertexArray.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hina
{

std::shared_ptr<VertexArray> VertexArray::Create() {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
