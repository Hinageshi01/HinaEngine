#pragma once

#include "Layer/Layer.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"


namespace Hina
{

// ImGui's bakend is GLFW + OpenGL at now.
// TODO : Abstract it to a base class and derive a ImGuiLayer_GLFW_OpenGL class.
class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event &e) override;

	virtual void Begin() override;
	virtual void OnImGuiRender() override;
	virtual void End() override;

	void BlockEvents(bool block) { m_blockEvents = block; }

	void SetDarkThemeColors();

	uint32_t GetActiveWidgetID() const;

private:
	bool m_blockEvents = true;
	float m_time = 0.0f;
};

} // namespace Hina
