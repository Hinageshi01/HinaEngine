#pragma once

#include "Core/Window.h"
#include "Event/ApplicationEvent.h"

namespace Hina
{

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event &e);

private:
	bool OnWindowClose(WindowCloseEvent &e);

	std::unique_ptr<Window> m_window;
	bool m_isRunning = false;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
