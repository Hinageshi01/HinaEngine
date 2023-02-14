#pragma once

#include "Layer/Layer.h"

namespace Hina
{

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer() : Layer("ImGuiLayer") {};

	// Return a raw pointer which must be handled by layer stack.
	static ImGuiLayer *Creat();
};

} // namespace Hina
