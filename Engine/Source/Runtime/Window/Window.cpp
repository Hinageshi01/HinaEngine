#include "hnpch.h"
#include "Window.h"

#ifdef HN_PLATFORM_WIN
	#include "Platform/Windows/WindowsWindow.h"
#else
	#error Hina only supports windows!
#endif

namespace Hina
{
std::unique_ptr<Window> Window::Create(const WindowInitializer &init) {

#ifdef HN_PLATFORM_WIN
	return std::make_unique<WindowsWindow>(init);
#endif

	HN_CORE_FATAL("Unknown Platform!");
	return nullptr;
}

} // namespace Hina
