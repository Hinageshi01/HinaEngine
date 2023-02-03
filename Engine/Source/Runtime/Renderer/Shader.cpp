#include "hnpch.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hina
{

std::shared_ptr<Shader> Shader::Create(
	const std::string &name,
	const std::string &vertexShaderPath,
	const std::string &fragmentShaderPath,
	const std::string &geometryShaderPath) {
	switch(Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexShaderPath, fragmentShaderPath, geometryShaderPath);
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
