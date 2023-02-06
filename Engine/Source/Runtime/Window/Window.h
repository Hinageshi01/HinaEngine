#pragma once

#include "Event/Event.h"

namespace Hina
{

struct WindowInitializer
{
	WindowInitializer() = default;
	WindowInitializer(
		std::string title, uint32_t width, uint32_t height,
		uint32_t major, uint32_t minor, uint32_t samples)
		: m_title(std::move(title)), m_width(width), m_height(height),
		m_major(major), m_minor(minor), m_samples(samples) {}

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
	static std::unique_ptr<Window> Create(const WindowInitializer &init = WindowInitializer());
};

} // namespace Hina
