#pragma once

namespace Hina
{

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
