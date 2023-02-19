#pragma once

#include "RenderCore/Shader.h"
#include "RenderCore/RenderAPI.h"

namespace Hina
{

class RenderCore
{
public:
	RenderCore() = delete;
	RenderCore(const RenderCore &) = delete;
	RenderCore &operator=(const RenderCore &) = delete;
	RenderCore(RenderCore &&) = delete;
	RenderCore &operator=(RenderCore &&) = delete;
	~RenderCore() = default;

	static void Init();
	static void Shutdown();

	static void BeginScene();
	static void EndScene();
	
	// Clear color, depth and stencil buffers.
	static void ClearBuffers(const glm::vec4 &color, const float depth = 1.0f);
	static void OnFrameResize(uint32_t width, uint32_t height);

	static void SetModelMatrix(const glm::mat4 &mat);
	static void SetViewMatrix(const glm::mat4 &mat);
	static void SetProjectionMatrix(const glm::mat4 &mat);

	static const uint32_t GetWidth() { return m_width; }
	static const uint32_t GetHeight() { return m_height; }

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray,
		const glm::mat4 &transform);

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray);

	// Maby we need to render one frame with multiple GraphicsAPI in the future?
	static void SetAPI(GraphicsAPI api) { RenderAPI::SetAPI(api); }
	static GraphicsAPI GetAPI() { return RenderAPI::GetAPI(); }

private:
	static glm::mat4 m_modelMatrix;
	static glm::mat4 m_viewMatrix;
	static glm::mat4 m_projectionMatrix;

	// Size of render ramebuffer.
	// As we use editor, it's always different whit window sizes.
	static uint32_t m_width;
	static uint32_t m_height;
};

} // namespace Hina
