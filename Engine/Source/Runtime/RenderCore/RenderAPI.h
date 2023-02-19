#pragma once

#include "RenderCore/VertexArray.h"

#include <glm/glm.hpp>

namespace Hina
{

enum class GraphicsAPI
{
	None = 0, OpenGL = 1
};

class RenderAPI
{
public:
	RenderAPI() = default;
	RenderAPI(const RenderAPI &) = default;
	RenderAPI &operator=(const RenderAPI &) = default;
	RenderAPI(RenderAPI &&) = default;
	RenderAPI &operator=(RenderAPI &&) = default;
	virtual ~RenderAPI() = default;

	virtual void Init() = 0;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

	virtual void SetClearColor(const glm::vec4 &color) = 0;
	virtual void SetClearDepth(const float depth) = 0;
	virtual void SetClearStencil(const int stencil) = 0;

	virtual void Clear() = 0;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount = 0) = 0;
	virtual void DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) = 0;

	virtual void SetLineWidth(float width) = 0;

	static void SetAPI(const GraphicsAPI api) { m_API = api; }
	static GraphicsAPI GetAPI() { return m_API; }
	static std::unique_ptr<RenderAPI> Create();

private:
	static GraphicsAPI m_API;
};

} // namespace Hina
