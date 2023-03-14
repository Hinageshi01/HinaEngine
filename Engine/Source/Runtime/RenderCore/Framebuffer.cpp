#include "hnpch.h"
#include "Framebuffer.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Hina
{

std::unique_ptr<Framebuffer> Framebuffer::Create(const FramebufferInitializer &init) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_unique<OpenGLFramebuffer>(init);
	}
	
	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
}

} // namespace Hina
