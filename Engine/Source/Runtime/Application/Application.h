#pragma once

#include "Core/Window.h"
#include "Event/ApplicationEvent.h"
#include "Layer/LayerStack.h"

namespace Hina
{

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
	bool OnWindowClose(WindowCloseEvent &e);

	std::unique_ptr<Window> m_window;
	bool m_isRunning = false;
	LayerStack m_layerStack;

	static Application *s_instance;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
