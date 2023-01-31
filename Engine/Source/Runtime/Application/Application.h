#pragma once

#include "Core/Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
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
	bool OnWindowClose(WindowCloseEvent &e);

	std::unique_ptr<Window> m_window;
	LayerStack m_layerStack;

	bool m_isRunning = false;

	static Application *s_instance;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
