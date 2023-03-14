#pragma once

namespace Hina
{

class RenderContext
{
public:
	static std::unique_ptr<RenderContext> Create(void *window);

public:
	RenderContext() = default;
	RenderContext(const RenderContext &) = default;
	RenderContext &operator=(const RenderContext &) = default;
	RenderContext(RenderContext &&) = default;
	RenderContext &operator=(RenderContext &&) = default;
	virtual ~RenderContext() = default;

	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;
};

}// namespace Hina
