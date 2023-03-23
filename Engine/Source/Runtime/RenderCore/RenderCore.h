#pragma once

#include "RenderCore/Shader.h"
#include "RenderCore/RenderAPI.h"

namespace Hina
{

class RenderCore final
{
public:
	RenderCore() = delete;
	RenderCore(const RenderCore &) = delete;
	RenderCore &operator=(const RenderCore &) = delete;
	RenderCore(RenderCore &&) = delete;
	RenderCore &operator=(RenderCore &&) = delete;
	~RenderCore() = default;

	static void SetAPI(const GraphicsAPI api);
	static GraphicsAPI GetAPI();

	static void Init();
	static void Shutdown();

	static void BeginScene();
	static void EndScene();
	
	static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);

	// Clear color, depth and stencil buffers.
	static void ClearBuffers(const glm::vec4 &color, const float depth = 1.0f);
	static void OnFrameResize(uint32_t width, uint32_t height);

	static void SetModelMatrix(const glm::mat4 &mat);
	static void SetModelMatrix(glm::mat4 &&mat);
	static void SetViewMatrix(const glm::mat4 &mat);
	static void SetViewMatrix(glm::mat4 &&mat);
	static void SetProjectionMatrix(const glm::mat4 &mat);
	static void SetProjectionMatrix(glm::mat4 &&mat);

	static const uint32_t GetWidth() { return m_width; }
	static const uint32_t GetHeight() { return m_height; }

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray,
		const glm::mat4 &transform);

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray);

private:
	static glm::mat4 m_modelMatrix;
	static glm::mat4 m_viewMatrix;
	static glm::mat4 m_projectionMatrix;

	// Size of rendering ramebuffer.
	// As we use editor, it's always different whit window sizes.
	static uint32_t m_width;
	static uint32_t m_height;
};

} // namespace Hina
