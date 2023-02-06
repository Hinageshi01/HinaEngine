#include "hnpch.h"
#include "Renderer.h"

namespace Hina
{

glm::mat4 Renderer::m_modelMatrix;
glm::mat4 Renderer::m_viewMatrix;
glm::mat4 Renderer::m_projectionMatrix;

void Renderer::Init() {
	HN_CORE_INFO("Initializing Renderer");
	RenderCommand::Init();
	m_modelMatrix = glm::identity<glm::mat4>();
}

void Renderer::Shutdown() {

}

void Renderer::BeginScene() {

}

void Renderer::EndScene() {

}

void Renderer::ClearBuffers(const glm::vec4 &color, const float depth) {
	RenderCommand::SetClearColor(color);
	RenderCommand::SetClearDepth(depth);
	RenderCommand::Clear();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
	RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::SetModelMatrix(const glm::mat4 &mat) {
	m_modelMatrix = mat;
}

void Renderer::SetViewMatrix(const glm::mat4 &mat) {
	m_viewMatrix = mat;
}

void Renderer::SetProjectionMatrix(const glm::mat4 &mat) {
	m_projectionMatrix = mat;
}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
	shader->Bind();
	shader->SetMat4("u_model", transform);
	shader->SetMat4("u_view", m_viewMatrix);
	shader->SetMat4("u_projection", m_projectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
	Submit(shader, vertexArray, m_modelMatrix);
}

} // namespace Hina
