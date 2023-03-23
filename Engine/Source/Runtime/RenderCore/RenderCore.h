#pragma once

#include "Camera/Camera.h"
#include "RenderCore/Framebuffer.h"
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
	
	static void OnFrameResize(const uint32_t width, const uint32_t height);
	static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);

	// Clear color, depth and stencil buffers.
	static void ClearBuffers(const glm::vec4 &color, const float depth = 1.0f);

	static void SetModelMatrix(const glm::mat4 &mat);
	static void SetModelMatrix(glm::mat4 &&mat);
	static void SetViewMatrix(const glm::mat4 &mat);
	static void SetViewMatrix(glm::mat4 &&mat);
	static void SetProjectionMatrix(const glm::mat4 &mat);
	static void SetProjectionMatrix(glm::mat4 &&mat);

	// Set primary camera controller.
	template<class T>
	static void SetCameraController(T &controller) {
		controller.SetCamera(m_pCamera);
	}
	// Get primary camera.
	static Camera &GetCamera() { return *m_pCamera; }

	// Get primary framebuffer.
	static Framebuffer &GetFramebuffer() { return *m_pFramebuffer; }
	// Id of primary framebuffer.
	static uint32_t GetFramebufferColorAttachmentRenderID();

	// Width of primary framebuffer.
	static uint32_t GetWidth();
	// Height of primary framebuffer.
	static uint32_t GetHeight();

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray,
		const glm::mat4 &transform);

	static void Submit(
		const std::shared_ptr<Shader> &shader,
		const std::shared_ptr<VertexArray> &vertexArray);

private:
	static std::shared_ptr<Camera> m_pCamera;
	static std::shared_ptr<Framebuffer> m_pFramebuffer;

	static glm::mat4 m_modelMatrix;
	static glm::mat4 m_viewMatrix;
	static glm::mat4 m_projectionMatrix;
};

} // namespace Hina
