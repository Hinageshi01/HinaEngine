#include "hnpch.h"
#include "RenderCore/Shader.h"

#include "RenderCore/RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hina
{

std::shared_ptr<Shader> Shader::Create(
	const std::string &name,
	const std::string &vertexShaderPath,
	const std::string &fragmentShaderPath,
	const std::string &geometryShaderPath) {
	switch(RenderAPI::GetAPI()) {
		case GraphicsAPI::None:
			HN_CORE_ERROR("RendererAPI::None is currently not supported!");
			return nullptr;

		case GraphicsAPI::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexShaderPath, fragmentShaderPath, geometryShaderPath);
	}

	HN_CORE_ERROR("Unknown RendererAPI!");
	return nullptr;
}

} // namespace Hina
