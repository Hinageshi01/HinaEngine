#include "hnpch.h"
#include "ImGuiLayer.h"

#ifdef HN_PLATFORM_WIN
	#include "Platform/ImGui/ImGuiLayer_GLFW_OpenGL.h"
#endif

#include "RenderCore/RenderAPI.h"

namespace Hina
{

ImGuiLayer *ImGuiLayer::Creat() {

#ifdef HN_PLATFORM_WIN
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::API::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return new ImGuiLayer_GLFW_OpenGL();
	}

	HN_CORE_ERROR("Rendering api undefined!");
	return nullptr;
#endif

	HN_CORE_FATAL("Platform undefined!");
	return nullptr;
}

} // namespace Hina
