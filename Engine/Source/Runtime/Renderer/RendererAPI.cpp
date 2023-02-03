#include "hnpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hina
{

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::Create() {
	switch(s_API) {
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLRendererAPI>();
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
