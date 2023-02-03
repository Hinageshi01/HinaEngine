#pragma once

#include "Renderer/RendererAPI.h"

namespace Hina
{

class RenderCommand
{
public:
	static void Init();

	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	static void SetClearColor(const glm::vec4 &color);
	// TODO : Expose the clear option.
	static void Clear();

	static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t indexCount = 0);
	static void DrawLines(const std::shared_ptr<VertexArray> &vertexArray, uint32_t vertexCount);
	static void SetLineWidth(float width);

private:
	static std::unique_ptr<RendererAPI> s_rendererAPI;
};

} // namespace Hina
