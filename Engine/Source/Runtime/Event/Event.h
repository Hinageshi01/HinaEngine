#pragma once

#include "Core/Binary.h"

#include <sstream>

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hina
{

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // Windows event.
	AppTick, AppUpdate, AppRender,                                        // Application event.
	KeyPressed, KeyReleased, KeyTyped,                                    // Key event.
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled    // Mouse event.
};

enum class EventCategory : uint8_t
{
	None = 0x00,
	Application = BIT8(0U),
	Input = BIT8(1U),
	Keyboard = BIT8(2U),
	Mouse = BIT8(3U),
	MouseButton = BIT8(4U),
};

class Event
{
public:
	Event() = default;
	Event(const Event &) = default;
	Event &operator=(const Event &) = default;
	Event(Event &&) = default;
	Event &operator=(Event &&) = default;
	virtual ~Event() = default;

	virtual EventType GetEventType() const = 0;
	virtual uint8_t GetCategoryFlags() const = 0;

	virtual const char *GetName() const = 0;
	// No need to override ToString if the derived class have no extra data to output.
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category) const {
		return GetCategoryFlags() & static_cast<uint8_t>(category);
	}

	bool m_isHandled = false;
};

class EventDispatcher final
{
public:
	explicit EventDispatcher(Event &event) : m_event(event) {}

	EventDispatcher() = delete;
	EventDispatcher(const EventDispatcher &) = default;
	EventDispatcher &operator=(const EventDispatcher &) = default;
	EventDispatcher(EventDispatcher &&) = default;
	EventDispatcher &operator=(EventDispatcher &&) = default;
	~EventDispatcher() = default;

	// F will be deduced by the compiler.
	template<typename T, typename F>
	bool Dispatch(const F &func) {
		if(m_event.GetEventType() == T::GetStaticType()) {
			m_event.m_isHandled |= func(static_cast<T &>(m_event));
			return true;
		}
		return false;
	}

private:
	Event &m_event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &event) {
	return os << event.ToString();
}

} // namespace Hina
