#pragma once

namespace Hina
{

class GraphicsContext
{
public:
	virtual ~GraphicsContext() = default;

	// TODO : What kind is the version number of other api?
	virtual void Init(const uint32_t major, const uint32_t minor) = 0;
	virtual void SwapBuffers() = 0;

	static std::unique_ptr<GraphicsContext> Create(void *window);
};

}// namespace Hina
