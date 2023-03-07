#include "hnpch.h"
#include "EditorContext.h"

#ifdef HN_PLATFORM_WIN
	#include "Platform/ImGui/ImGui_GLFW_OpenGL.h"
#endif

#include "RenderCore/RenderAPI.h"

namespace Hina
{

std::unique_ptr<EditorContext> EditorContext::Creat() {

#ifdef HN_PLATFORM_WIN
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::API::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<ImGui_GLFW_OpenGL>();
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
#endif

	HN_CORE_FATAL("Unknown Platform!");
	return nullptr;
}

} // namespace Hina
