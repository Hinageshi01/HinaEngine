#include "hnpch.h"

#include "Window.h"

#ifdef HN_PLATFORM_WIN
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Hina
{
std::unique_ptr<Window> Window::Create(const WindowProps &props) {

#ifdef HN_PLATFORM_WIN
	return std::make_unique<WindowsWindow>(props);
#endif

}

} // namespace Hina
