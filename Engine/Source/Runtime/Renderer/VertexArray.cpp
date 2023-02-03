#include "hnpch.h"
#include "VertexArray.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hina
{

std::shared_ptr<VertexArray> VertexArray::Create() {
	switch(RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr; break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
