#pragma once

#include "Event/Event.h"
#include "Core/KeyCodes.h"

namespace Hina
{

class KeyEvent : public Event
{
public:
	KeyEvent() = delete;
	KeyEvent(const KeyEvent &) = default;
	KeyEvent &operator=(const KeyEvent &) = default;
	KeyEvent(KeyEvent &&) = default;
	KeyEvent &operator=(KeyEvent &&) = default;
	~KeyEvent() = default;

	KeyCode GetKeyCode() const { return m_keyCode; }

	virtual uint8_t GetCategoryFlags() const override {
		return EventCategory::Keyboard | EventCategory::Input;
	}

protected:
	KeyEvent(const KeyCode keycode)
		: m_keyCode(keycode) {}

	KeyCode m_keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
		: KeyEvent(keycode), m_isRepeat(isRepeat) {}

	KeyPressedEvent() = delete;
	KeyPressedEvent(const KeyPressedEvent &) = default;
	KeyPressedEvent &operator=(const KeyPressedEvent &) = default;
	KeyPressedEvent(KeyPressedEvent &&) = default;
	KeyPressedEvent &operator=(KeyPressedEvent &&) = default;
	~KeyPressedEvent() = default;

	bool IsRepeat() const { return m_isRepeat; }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_keyCode << " (repeat = " << m_isRepeat << ")";
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::KeyPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "KeyPressed"; }

private:
	bool m_isRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(const KeyCode keycode)
		: KeyEvent(keycode) {}

	KeyReleasedEvent() = delete;
	KeyReleasedEvent(const KeyReleasedEvent &) = default;
	KeyReleasedEvent &operator=(const KeyReleasedEvent &) = default;
	KeyReleasedEvent(KeyReleasedEvent &&) = default;
	KeyReleasedEvent &operator=(KeyReleasedEvent &&) = default;
	~KeyReleasedEvent() = default;

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_keyCode;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::KeyReleased; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "KeyReleased"; }
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(const KeyCode keycode)
		: KeyEvent(keycode) {}

	KeyTypedEvent() = delete;
	KeyTypedEvent(const KeyTypedEvent &) = default;
	KeyTypedEvent &operator=(const KeyTypedEvent &) = default;
	KeyTypedEvent(KeyTypedEvent &&) = default;
	KeyTypedEvent &operator=(KeyTypedEvent &&) = default;
	~KeyTypedEvent() = default;

	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_keyCode;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::KeyTyped; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "KeyTyped"; }
};

}
