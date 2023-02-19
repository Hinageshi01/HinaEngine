#include "hnpch.h"
#include "RenderCommand.h"

namespace Hina
{

std::unique_ptr<RenderAPI> RenderCommand::ms_renderAPI;

void RenderCommand::Init() {
	ms_renderAPI = RenderAPI::Create();
	ms_renderAPI->Init();
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	ms_renderAPI->SetViewport(x, y, width, height);
}

void RenderCommand::SetClearColor(const glm::vec4 &color) {
	ms_renderAPI->SetClearColor(color);
}

void RenderCommand::SetClearDepth(const float depth) {
	ms_renderAPI->SetClearDepth(depth);
}

void RenderCommand::SetClearStencil(const int stencil) {
	ms_renderAPI->SetClearStencil(stencil);
}

void RenderCommand::Clear() {
	ms_renderAPI->Clear();
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount) {
	ms_renderAPI->DrawIndexed(vertexArray, indexCount);
}

void RenderCommand::DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) {
	ms_renderAPI->DrawLines(vertexArray, vertexCount);
}

void RenderCommand::SetLineWidth(float width) {
	ms_renderAPI->SetLineWidth(width);
}

} // namespace Hina
