#pragma once

#include "Core/Timer.h"

namespace Hina
{

class EditorProfiler final
{
public:
	EditorProfiler() = default;
	EditorProfiler(const EditorProfiler &) = default;
	EditorProfiler &operator=(const EditorProfiler &) = default;
	EditorProfiler(EditorProfiler &&) = default;
	EditorProfiler &operator=(EditorProfiler &&) = default;
	~EditorProfiler() = default;

	// Must and can only be called once in the main loop.
	void OnImGuiRender();

private:
	// Update per 0.5 seconds.
	float GetFPS();

	Timer m_timer;

	float m_second = 0.0f;
	float m_frams = 0.0f;
	float m_fps = 0.0f;
};

} // namespace Hina
