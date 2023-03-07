#include "hnpch.h"
#include "RenderContext.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hina
{

std::unique_ptr<RenderContext> RenderContext::Create(void *window) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window));
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
}

} // namespace Hina
