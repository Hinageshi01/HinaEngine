#include "hnpch.h"
#include "RenderContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "RenderCore/RenderAPI.h"

namespace Hina
{

std::unique_ptr<RenderContext> RenderContext::Create(void *window) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window));

		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr;
	}

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
