#include "hnpch.h"
#include "RenderCore/Texture2D.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hina
{

std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("GraphicsAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
	}

	HN_CORE_ERROR("Unknown Graphics API!");
	return nullptr;
}

} // namespace Hina
