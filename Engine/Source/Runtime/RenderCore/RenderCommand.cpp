#include "hnpch.h"
#include "RenderCommand.h"

namespace Hina
{

std::unique_ptr<RenderAPI> RenderCommand::m_renderAPI;

void RenderCommand::Init() {
	m_renderAPI = RenderAPI::Create();
	m_renderAPI->Init();
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	m_renderAPI->SetViewport(x, y, width, height);
}

void RenderCommand::SetClearColor(const glm::vec4 &color) {
	m_renderAPI->SetClearColor(color);
}

void RenderCommand::SetClearDepth(const float depth) {
	m_renderAPI->SetClearDepth(depth);
}

void RenderCommand::SetClearStencil(const int stencil) {
	m_renderAPI->SetClearStencil(stencil);
}

void RenderCommand::Clear() {
	m_renderAPI->Clear();
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount) {
	m_renderAPI->DrawIndexed(vertexArray, indexCount);
}

void RenderCommand::DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) {
	m_renderAPI->DrawLines(vertexArray, vertexCount);
}

void RenderCommand::SetLineWidth(float width) {
	m_renderAPI->SetLineWidth(width);
}

} // namespace Hina
