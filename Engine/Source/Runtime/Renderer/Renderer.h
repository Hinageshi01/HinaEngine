#pragma once

#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"
#include "Camera/Camera.h"

namespace Hina
{

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;
	Renderer(Renderer &&) = delete;
	Renderer &operator=(Renderer &&) = delete;
	~Renderer() = default;

	static void Init();
	static void Shutdown();

	static void BeginScene();
	static void EndScene();
	
	static void OnWindowResize(uint32_t width, uint32_t height);

	static void SetModelMatrix(const glm::mat4 &mat);
	static void SetViewMatrix(const glm::mat4 &mat);
	static void SetProjectionMatrix(const glm::mat4 &mat);

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray,
		const glm::mat4 &transform);

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray);

	static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
	static glm::mat4 m_modelMatrix;
	static glm::mat4 m_viewMatrix;
	static glm::mat4 m_projectionMatrix;
};

} // namespace Hina
