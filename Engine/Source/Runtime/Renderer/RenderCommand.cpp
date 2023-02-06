#include "hnpch.h"
#include "RenderCommand.h"

namespace Hina
{

std::unique_ptr<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::Create();

void RenderCommand::Init() {
	s_rendererAPI->Init();
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	s_rendererAPI->SetViewport(x, y, width, height);
}

void RenderCommand::SetClearColor(const glm::vec4 &color) {
	s_rendererAPI->SetClearColor(color);
}

void RenderCommand::SetClearDepth(const float depth) {
	s_rendererAPI->SetClearDepth(depth);
}

void RenderCommand::Clear() {
	s_rendererAPI->Clear();
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount) {
	s_rendererAPI->DrawIndexed(vertexArray, indexCount);
}

void RenderCommand::DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) {
	s_rendererAPI->DrawLines(vertexArray, vertexCount);
}

void RenderCommand::SetLineWidth(float width) {
	s_rendererAPI->SetLineWidth(width);
}

} // namespace Hina
