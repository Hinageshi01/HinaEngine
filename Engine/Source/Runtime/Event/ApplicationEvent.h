#pragma once

#include "Event/Event.h"

namespace Hina
{

class WindowResizeEvent final : public Event
{
public:
	WindowResizeEvent(const uint32_t width, const uint32_t height)
		: m_width(width), m_height(height) {}

	WindowResizeEvent() = delete;
	WindowResizeEvent(const WindowResizeEvent &) = default;
	WindowResizeEvent &operator=(const WindowResizeEvent &) = default;
	WindowResizeEvent(WindowResizeEvent &&) = default;
	WindowResizeEvent &operator=(WindowResizeEvent &&) = default;
	~WindowResizeEvent() = default;

	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }

	static EventType GetStaticType() { return EventType::WindowResize; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Application);
	}

	virtual const char *GetName() const override { return "WindowResize"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_width << ", " << m_height;
		return ss.str();
	}

private:
	unsigned int m_width, m_height;
};

class WindowCloseEvent final : public Event
{
public:
	WindowCloseEvent() = default;
	WindowCloseEvent(const WindowCloseEvent &) = default;
	WindowCloseEvent &operator=(const WindowCloseEvent &) = default;
	WindowCloseEvent(WindowCloseEvent &&) = default;
	WindowCloseEvent &operator=(WindowCloseEvent &&) = default;
	~WindowCloseEvent() = default;

	static EventType GetStaticType() { return EventType::WindowClose; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Application);
	}

	virtual const char *GetName() const override { return "WindowClose"; }
};

class AppTickEvent final : public Event
{
public:
	AppTickEvent() = default;
	AppTickEvent(const AppTickEvent &) = default;
	AppTickEvent &operator=(const AppTickEvent &) = default;
	AppTickEvent(AppTickEvent &&) = default;
	AppTickEvent &operator=(AppTickEvent &&) = default;
	~AppTickEvent() = default;

	static EventType GetStaticType() { return EventType::AppTick; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Application);
	}

	virtual const char *GetName() const override { return "AppTick"; }
};

class AppUpdateEvent final : public Event
{
public:
	AppUpdateEvent() = default;
	AppUpdateEvent(const AppUpdateEvent &) = default;
	AppUpdateEvent &operator=(const AppUpdateEvent &) = default;
	AppUpdateEvent(AppUpdateEvent &&) = default;
	AppUpdateEvent &operator=(AppUpdateEvent &&) = default;
	~AppUpdateEvent() = default;

	static EventType GetStaticType() { return EventType::AppUpdate; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Application);
	}

	virtual const char *GetName() const override { return "AppUpdate"; }
};

class AppRenderEvent final : public Event
{
public:
	AppRenderEvent() = default;
	AppRenderEvent(const AppRenderEvent &) = default;
	AppRenderEvent &operator=(const AppRenderEvent &) = default;
	AppRenderEvent(AppRenderEvent &&) = default;
	AppRenderEvent &operator=(AppRenderEvent &&) = default;
	~AppRenderEvent() = default;

	static EventType GetStaticType() { return EventType::AppRender; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Application);
	}

	virtual const char *GetName() const override { return "AppRender"; }
};

} // namespace Hina
