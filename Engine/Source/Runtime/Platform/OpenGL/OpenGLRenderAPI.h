#pragma once

#include "RenderCore/RenderAPI.h"

namespace Hina
{

class OpenGLRenderAPI final : public RenderAPI
{
public:
	OpenGLRenderAPI();
	OpenGLRenderAPI(const OpenGLRenderAPI &) = default;
	OpenGLRenderAPI &operator=(const OpenGLRenderAPI &) = default;
	OpenGLRenderAPI(OpenGLRenderAPI &&) = default;
	OpenGLRenderAPI &operator=(OpenGLRenderAPI &&) = default;
	~OpenGLRenderAPI() = default;

	virtual void Init() override;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	virtual void SetClearColor(const glm::vec4 &color) override;
	virtual void SetClearDepth(const float depth) override;
	virtual void SetClearStencil(const int stencial) override;

	virtual void Clear() override;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount = 0) override;
	virtual void DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) override;

	virtual void SetLineWidth(float width) override;
};

} // namespace Hina
