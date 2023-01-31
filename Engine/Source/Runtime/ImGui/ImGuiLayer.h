#pragma once

#include "Layer/Layer.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace Hina
{

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event &e) override;
	virtual void OnUpdate() override;

	void Begin();
	void End();

	void BlockEvents(bool block) { m_BlockEvents = block; }

	void SetDarkThemeColors();

	uint32_t GetActiveWidgetID() const;

private:
	bool m_BlockEvents = true;
	float m_time = 0.0f;
};

} // namespace Hina
