#include "hnpch.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Hina
{

GraphicsAPI RenderAPI::m_API = GraphicsAPI::None;

std::unique_ptr<RenderAPI> RenderAPI::Create() {
	switch(m_API) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLRenderAPI>();
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
}

} // namespace Hina
