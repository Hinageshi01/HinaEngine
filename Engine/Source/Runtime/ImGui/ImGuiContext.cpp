#include "hnpch.h"
#include "ImGuiContext.h"

#ifdef HN_PLATFORM_WIN
	#include "Platform/ImGui/ImGuiContext_GLFW_OpenGL.h"
#endif

#include "RenderCore/RenderAPI.h"

namespace Hina
{

std::unique_ptr<ImGuiContext> ImGuiContext::Creat() {

#ifdef HN_PLATFORM_WIN
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::API::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<ImGuiContext_GLFW_OpenGL>();
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
#endif

	HN_CORE_FATAL("Unknown Platform!");
	return nullptr;
}

} // namespace Hina
