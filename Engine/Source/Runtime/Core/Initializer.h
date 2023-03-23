#pragma once

#include "RenderCore/RenderAPI.h"
#include "Window/Window.h"

#include <cstdint>

namespace Hina
{

struct Initializer final
{
	GraphicsAPI m_api = Hina::GraphicsAPI::None;
	WindowInitializer m_window;
};

} // namespace Hina
