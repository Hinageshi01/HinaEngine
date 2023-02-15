#include "hnpch.h"
#include "RenderCore.h"

namespace Hina
{

glm::mat4 RenderCore::ms_modelMatrix;
glm::mat4 RenderCore::ms_viewMatrix;
glm::mat4 RenderCore::ms_projectionMatrix;

void RenderCore::Init() {
	HN_PROFILE_FUNCTION();

	HN_CORE_INFO("Initializing Renderer");
	RenderCommand::Init();
	ms_modelMatrix = glm::identity<glm::mat4>();
}

void RenderCore::Shutdown() {

}

void RenderCore::BeginScene() {

}

void RenderCore::EndScene() {

}

void RenderCore::ClearBuffers(const glm::vec4 &color, const float depth, const int stencil) {
	HN_PROFILE_FUNCTION();

	RenderCommand::SetClearColor(color);
	RenderCommand::SetClearDepth(depth);
	RenderCommand::SetClearStencil(stencil);
	RenderCommand::Clear();
}

void RenderCore::OnWindowResize(uint32_t width, uint32_t height) {
	RenderCommand::SetViewport(0, 0, width, height);
}

void RenderCore::SetModelMatrix(const glm::mat4 &mat) {
	ms_modelMatrix = mat;
}

void RenderCore::SetViewMatrix(const glm::mat4 &mat) {
	ms_viewMatrix = mat;
}

void RenderCore::SetProjectionMatrix(const glm::mat4 &mat) {
	ms_projectionMatrix = mat;
}

void RenderCore::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
	HN_PROFILE_FUNCTION();
	
	shader->Bind();
	shader->SetMat4("u_model", transform);
	shader->SetMat4("u_view", ms_viewMatrix);
	shader->SetMat4("u_projection", ms_projectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void RenderCore::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
	Submit(shader, vertexArray, ms_modelMatrix);
}

} // namespace Hina
