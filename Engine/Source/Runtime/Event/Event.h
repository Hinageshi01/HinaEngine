#pragma once

#include "Binary/Binary.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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

// Event category type.
using EVT_CAT_TYP = uint8_t;

enum class EventCategory : EVT_CAT_TYP
{
	None = 0x00,
	Application = BIT8(0U),
	Input = BIT8(1U),
	Keyboard = BIT8(2U),
	Mouse = BIT8(3U),
	MouseButton = BIT8(4U)
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
	virtual const char *GetName() const = 0;
	virtual EVT_CAT_TYP GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category) {
		return GetCategoryFlags() & static_cast<EVT_CAT_TYP>(category);
	}

	bool m_isHandled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event &event) : m_Event(event) {}

	// F will be deduced by the compiler.
	template<typename T, typename F>
	bool Dispatch(const F &func) {
		if(m_Event.GetEventType() == T::GetStaticType()) {
			m_Event.m_isHandled |= func(static_cast<T &>(m_Event));
			return true;
		}
		return false;
	}

private:
	Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &event) {
	return os << event.ToString();
}

} // namespace Hina
