#pragma once

#include "RenderCore/RenderAPI.h"

namespace Hina
{

class RenderCommand
{
public:
	RenderCommand() = delete;
	RenderCommand(const RenderCommand &) = delete;
	RenderCommand &operator=(const RenderCommand &) = delete;
	RenderCommand(RenderCommand &&) = delete;
	RenderCommand &operator=(RenderCommand &&) = delete;
	~RenderCommand() = default;

	static void Init();

	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	static void SetClearColor(const glm::vec4 &color);
	static void SetClearDepth(const float depth);
	static void SetClearStencil(const int stencil);

	static void Clear();

	static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount = 0);
	static void DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount);

	static void SetLineWidth(float width);

private:
	static std::unique_ptr<RenderAPI> m_renderAPI;
};

} // namespace Hina
