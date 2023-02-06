#pragma once

#include "Event/Event.h"

namespace Hina
{

struct WindowProps
{
	WindowProps(std::string title = "Hina Engine", uint32_t width = 1280, uint32_t height = 720)
		: m_title(std::move(title)), m_width(width), m_height(height) {}

	std::string m_title;
	uint32_t m_width;
	uint32_t m_height;
};

class Window
{
public:
	using EventCallbackFn = std::function<void(Event &)>;

	virtual ~Window() = default;

	virtual void BeginOfFrame() = 0;
	virtual void OnUpdate() = 0;
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
	static std::unique_ptr<Window> Create(const WindowProps &props = WindowProps());
};

} // namespace Hina
