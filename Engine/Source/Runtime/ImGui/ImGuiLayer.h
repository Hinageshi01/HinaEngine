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

	virtual void BeginOfFrame() override;
	virtual void OnImGuiRender() override;
	virtual void EndOfFrame() override;

	void BlockEvents(bool block) { m_BlockEvents = block; }

	void SetDarkThemeColors();

	uint32_t GetActiveWidgetID() const;

private:
	bool m_BlockEvents = true;
	float m_time = 0.0f;
};

} // namespace Hina
