#include "hnpch.h"
#include "RenderCore.h"

#include "RenderCore/RenderCommand.h"
#include "Application/Application.h"

namespace Hina
{

glm::mat4 RenderCore::m_modelMatrix;
glm::mat4 RenderCore::m_viewMatrix;
glm::mat4 RenderCore::m_projectionMatrix;

uint32_t RenderCore::m_width;
uint32_t RenderCore::m_height;

void RenderCore::Init() {
	HN_PROFILE_FUNCTION();

	HN_CORE_INFO("Initializing Renderer");
	RenderCommand::Init();

	// I'm not sure about the design here yet.
	// RenderCore::size will be initialized as Window::size before the first frame.
	// But RenderCore::size will be reset to Framebuffer::size at the first frame.
	const Window &window = Application::Get().GetWindow();
	m_width = window.GetWidth();
	m_height = window.GetHeight();
	m_modelMatrix = glm::identity<glm::mat4>();
}

void RenderCore::Shutdown() {

}

void RenderCore::BeginScene() {

}

void RenderCore::EndScene() {

}

void RenderCore::ClearBuffers(const glm::vec4 &color, const float depth) {
	HN_PROFILE_FUNCTION();

	RenderCommand::SetClearColor(color);
	RenderCommand::SetClearDepth(depth);
	RenderCommand::Clear();
}

void RenderCore::OnFrameResize(uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;
}

void RenderCore::SetModelMatrix(const glm::mat4 &mat) {
	m_modelMatrix = mat;
}

void RenderCore::SetViewMatrix(const glm::mat4 &mat) {
	m_viewMatrix = mat;
}

void RenderCore::SetProjectionMatrix(const glm::mat4 &mat) {
	m_projectionMatrix = mat;
}

void RenderCore::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
	HN_PROFILE_FUNCTION();
	
	shader->Bind();
	shader->SetMat4("u_model", transform);
	shader->SetMat4("u_view", m_viewMatrix);
	shader->SetMat4("u_projection", m_projectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void RenderCore::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
	Submit(shader, vertexArray, m_modelMatrix);
}

} // namespace Hina
