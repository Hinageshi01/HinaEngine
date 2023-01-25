#pragma once

#include <iostream>

#include "Core.h"

namespace Hina
{

class HN_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

// To be defined in example.
Application *CreateApplication();

}
