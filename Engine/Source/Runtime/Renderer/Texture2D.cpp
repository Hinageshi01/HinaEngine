#include "hnpch.h"
#include "Renderer/Texture2D.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hina
{

std::shared_ptr<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height) {
	switch(Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(width, height);
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path) {
	switch(Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
