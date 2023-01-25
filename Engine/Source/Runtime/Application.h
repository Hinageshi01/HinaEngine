#pragma once

#include "Core.h"
#include <iostream>

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
