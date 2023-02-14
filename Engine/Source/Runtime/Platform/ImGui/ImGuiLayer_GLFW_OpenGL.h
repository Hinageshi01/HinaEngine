#pragma once

#include "Event/Event.h"
#include "ImGui/ImGuiLayer.h"

namespace Hina
{

class ImGuiLayer_GLFW_OpenGL final : public ImGuiLayer
{
public:
	ImGuiLayer_GLFW_OpenGL() = default;
	ImGuiLayer_GLFW_OpenGL(const ImGuiLayer_GLFW_OpenGL &) = default;
	ImGuiLayer_GLFW_OpenGL &operator=(const ImGuiLayer_GLFW_OpenGL &) = default;
	ImGuiLayer_GLFW_OpenGL(ImGuiLayer_GLFW_OpenGL &&) = default;
	ImGuiLayer_GLFW_OpenGL &operator=(ImGuiLayer_GLFW_OpenGL &&) = default;
	~ImGuiLayer_GLFW_OpenGL() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event &e) override;

	virtual void Begin() override;
	virtual void End() override;

	void BlockEvents(bool block);
	void SetDarkThemeColors();
	uint32_t GetActiveWidgetID() const;

private:
	bool m_blockEvents = true;
	float m_time = 0.0f;
};

} // namespace Hina
