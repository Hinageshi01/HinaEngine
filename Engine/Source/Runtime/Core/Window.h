#pragma once

#include "Event/Event.h"

#include <sstream>

namespace Hina
{

struct WindowProps
{
	WindowProps(std::string title = "Hina Engine",
		uint32_t width = 1280, uint32_t height = 720)
		: Title(std::move(title)), Width(width), Height(height) {}

	std::string Title;
	uint32_t Width;
	uint32_t Height;
};

// Interface representing a desktop system based Window
class Window
{
public:
	using EventCallbackFn = std::function<void(Event &)>;

	virtual ~Window() = default;

	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void *GetNativeWindow() const = 0;

	static std::unique_ptr<Window> Create(const WindowProps &props = WindowProps());
};

} // namespace Hina
