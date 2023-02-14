#pragma once

#include "Window/Window.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "ImGui/ImGuiLayer.h"
#include "Layer/LayerStack.h"

namespace Hina
{

// Application is a singleton.
class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event &e);

	void PushLater(Layer * layer);
	void PushOverlay(Layer * layer);

	static Application &Get() { return *s_instance; }
	Window &GetWindow() { return *m_window; }

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

	std::unique_ptr<Window> m_window;
	ImGuiLayer *m_imguiLayer;
	LayerStack m_layerStack;
	
	static Application *s_instance;
	
	bool m_isRunning = false;
	bool m_isMinimized = false;
	float m_lastFrameTime = 0.0f;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
