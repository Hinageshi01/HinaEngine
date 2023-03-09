#include "hnpch.h"
#include "EditorProfiler.h"

#include <ImGui/imgui.h>

namespace Hina
{

namespace
{
constexpr float UPDATE_FREQUENCY = 0.5f;
}

void EditorProfiler::OnImGuiRender() {
	
	ImGui::Begin("Profiler");

	ImGui::Text("FPS: %.1f", GetFPS());
	ImGui::Text("One frame: %.3f ms", m_timer.ElapsedMillis());

	m_timer.Reset();

	ImGui::End();
}

float EditorProfiler::GetFPS() {
	m_second += m_timer.ElapsedSeconds();
	++m_frams;

	if(m_second >= UPDATE_FREQUENCY) {
		m_fps = m_frams / m_second;

		m_frams = 0.0f;
		m_second = 0.0f;
	}

	return m_fps;
}

} // namespace Hina
