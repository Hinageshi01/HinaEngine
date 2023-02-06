#include "hnpch.h"

#include "RendererContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Renderer/RendererAPI.h"

namespace Hina
{

std::unique_ptr<RendererContext> RendererContext::Create(void *window) {
	switch(RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window)); break;

		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr; break;
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
