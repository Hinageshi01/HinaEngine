#include "hnpch.h"
#include "Framebuffer.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Hina
{

std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferInitializer &init) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLFramebuffer>(init);
	}
	
	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
