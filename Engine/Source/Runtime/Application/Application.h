#pragma once

#include "Core/Window.h"

namespace Hina
{

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

private:
	std::unique_ptr<Window> m_window;
	bool m_isRunning = false;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
