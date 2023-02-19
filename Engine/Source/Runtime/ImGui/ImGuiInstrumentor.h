#pragma once

#include "Core/Timer.h"

namespace Hina
{

class ImGuiInstrumentor final
{
public:
	ImGuiInstrumentor() = default;
	ImGuiInstrumentor(const ImGuiInstrumentor &) = default;
	ImGuiInstrumentor &operator=(const ImGuiInstrumentor &) = default;
	ImGuiInstrumentor(ImGuiInstrumentor &&) = default;
	ImGuiInstrumentor &operator=(ImGuiInstrumentor &&) = default;
	~ImGuiInstrumentor() = default;

	// Must and can only be called once in the main loop.
	void Draw(const char *title);

private:
	// Update per 0.5 seconds.
	float GetFPS();

	Timer timer;

	float m_second = 0.0f;
	float m_frams = 0.0f;
	float m_fps = 0.0f;
};

} // namespace Hina
