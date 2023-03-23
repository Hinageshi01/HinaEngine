#include "hnpch.h"
#include "RenderCore.h"

#include "RenderCore/RenderCommand.h"
#include "Application/Application.h"

namespace Hina
{

glm::mat4 RenderCore::m_modelMatrix;
glm::mat4 RenderCore::m_viewMatrix;
glm::mat4 RenderCore::m_projectionMatrix;

std::shared_ptr<Camera> RenderCore::m_pCamera;
std::shared_ptr<Framebuffer> RenderCore::m_pFramebuffer;

void RenderCore::SetAPI(const GraphicsAPI api) {
	RenderCommand::SetAPI(api);
}

GraphicsAPI RenderCore::GetAPI() {
	return RenderCommand::GetAPI();
}

void RenderCore::Init() {
	HN_PROFILE_FUNCTION();

	HN_CORE_INFO("Initializing Renderer");
	RenderCommand::Init();

	m_pCamera = std::make_shared<Camera>();
	auto cameraEntitty = Application::Get().GetScene().CreateEntity("Primary Camera");
	cameraEntitty.AddComponent<CameraComponent>(m_pCamera);
	
	m_pFramebuffer = Framebuffer::Create();

	m_modelMatrix = glm::identity<glm::mat4>();
}

void RenderCore::Shutdown() {

}

void RenderCore::BeginScene() {

}

void RenderCore::EndScene() {

}

void RenderCore::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) {
	RenderCommand::SetViewport(x, y, width, height);
}

void RenderCore::ClearBuffers(const glm::vec4 &color, const float depth) {
	HN_PROFILE_FUNCTION();

	RenderCommand::SetClearColor(color);
	RenderCommand::SetClearDepth(depth);
	RenderCommand::Clear();
}

void RenderCore::OnFrameResize(const uint32_t width, const uint32_t height) {
	m_pFramebuffer->Resize(width, height);
	SetViewport(0, 0, width, height);
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

void RenderCore::SetModelMatrix() {
	m_modelMatrix = glm::identity<glm::mat4>();
}

void RenderCore::SetViewMatrix() {
	m_viewMatrix = m_pCamera->GetViewMatrix();
}

void RenderCore::SetProjectionMatrix() {
	m_projectionMatrix = m_pCamera->GetProjectionMatrix(m_pFramebuffer->GetWidth(), m_pFramebuffer->GetHeight());
}

uint32_t RenderCore::GetFramebufferColorAttachmentRenderID() {
	return m_pFramebuffer->GetColorAttachmentRenderID();
}

uint32_t RenderCore::GetWidth() {
	return m_pFramebuffer->GetWidth();
}

uint32_t RenderCore::GetHeight() {
	return m_pFramebuffer->GetHeight();
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
