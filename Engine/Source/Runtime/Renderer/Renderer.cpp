#include "hnpch.h"
#include "Renderer.h"

namespace Hina
{

glm::mat4 Renderer::m_modelMatrix;
glm::mat4 Renderer::m_viewProjection;

void Renderer::Init() {
	RenderCommand::Init();
}

void Renderer::Shutdown() {

}

void Renderer::BeginScene() {

}

void Renderer::EndScene() {

}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
	RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::SetModelMatrix(const glm::mat4 &mat) {
	m_modelMatrix = mat;
}

void Renderer::SetViewProjectionMatrix(const glm::mat4 &mat) {
	m_viewProjection = mat;
}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
	shader->Bind();
	shader->SetMat4("u_model", transform);
	shader->SetMat4("u_viewProjection", m_viewProjection);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
	Submit(shader, vertexArray, m_modelMatrix);
}

} // namespace Hina
