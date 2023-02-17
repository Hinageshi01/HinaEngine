#include "hnpch.h"
#include "Framebuffer.h"

#include "RenderCore/RenderCore.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Hina
{

std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferInitializer &init) {
	switch(RenderCore::GetAPI()) {
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
