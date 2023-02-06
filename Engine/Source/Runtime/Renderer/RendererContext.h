#pragma once

namespace Hina
{

class RendererContext
{
public:
	virtual ~RendererContext() = default;

	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;

	static std::unique_ptr<RendererContext> Create(void *window);
};

}// namespace Hina
