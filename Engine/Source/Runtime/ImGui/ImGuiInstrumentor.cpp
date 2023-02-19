#include "hnpch.h"
#include "ImGuiInstrumentor.h"

#include <ImGui/imgui.h>

namespace Hina
{

namespace
{
constexpr float UPDATE_FREQUENCY = 0.5f;
}

void ImGuiInstrumentor::Draw(const char *title) {
	ImGui::Begin(title);

	ImGui::Text("FPS: %.1f", GetFPS());
	ImGui::Text("One frame: %.3f ms", timer.ElapsedMillis());

	timer.Reset();

	ImGui::End();
}

float ImGuiInstrumentor::GetFPS() {
	m_second += timer.ElapsedSeconds();
	++m_frams;

	if(m_second >= UPDATE_FREQUENCY) {
		m_fps = m_frams / m_second;

		m_frams = 0.0f;
		m_second = 0.0f; 
	}

	return m_fps;
}

} // namespace Hina
