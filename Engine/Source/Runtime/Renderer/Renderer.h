#pragma once

#include "Renderer/RenderCommand.h"

#include "Renderer/Shader.h"

namespace Hina
{

class Renderer
{
public:
	static void Init();
	static void Shutdown();

	static void OnWindowResize(uint32_t width, uint32_t height);

	static void BeginScene();
	static void EndScene();

	static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

	static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
	static glm::mat4 ViewProjectionMatrix;
};

} // namespace Hina
