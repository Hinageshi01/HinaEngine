#pragma once

#include "Event/Event.h"

namespace Hina
{

struct WindowInitializer
{
	std::string m_title = "Hina Engine";
	uint32_t m_width = 1280;
	uint32_t m_height = 720;

	uint32_t m_major = 4;
	uint32_t m_minor = 6;
	uint32_t m_samples = 4;
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event &)>;

	Window() = default;
	Window(const Window &) = default;
	Window &operator=(const Window &) = default;
	Window(Window &&) = default;
	Window &operator=(Window &&) = default;
	virtual ~Window() = default;

	virtual void EndOfFrame() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;
	virtual float GetTime() const = 0;

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void *GetNativeWindow() const = 0;

	// Creat a derived class of Window which determined by the platform.
	static std::unique_ptr<Window> Create(const WindowInitializer &init = WindowInitializer());
};

} // namespace Hina
