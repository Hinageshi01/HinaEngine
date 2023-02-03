#include "hnpch.h"
#include "Renderer.h"

namespace Hina
{

glm::mat4 Renderer::ViewProjectionMatrix;

void Renderer::Init() {
	RenderCommand::Init();
}

void Renderer::Shutdown() {

}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
	RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene() {

}

void Renderer::EndScene() {

}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
	shader->Bind();
	// shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	// shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

} // namespace Hina