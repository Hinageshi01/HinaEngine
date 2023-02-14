#pragma once

#include "Event/Event.h"

#include "Core/KeyCodes.h"

namespace Hina
{

class KeyPressEvent final : public Event
{
public:
	KeyPressEvent(const KeyCode keycode, const bool isRepeat = false)
		: m_keyCode(keycode), m_isRepeat(isRepeat) {}

	KeyPressEvent() = delete;
	KeyPressEvent(const KeyPressEvent &) = default;
	KeyPressEvent &operator=(const KeyPressEvent &) = default;
	KeyPressEvent(KeyPressEvent &&) = default;
	KeyPressEvent &operator=(KeyPressEvent &&) = default;
	~KeyPressEvent() = default;

	bool IsRepeat() const { return m_isRepeat; }

	static EventType GetStaticType() { return EventType::KeyPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Keyboard) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "KeyPress"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_keyCode << " (repeat = " << m_isRepeat << ")";
		return ss.str();
	}

private:
	KeyCode m_keyCode;
	bool m_isRepeat = false;
};

class KeyReleaseEvent final : public Event
{
public:
	explicit KeyReleaseEvent(const KeyCode keycode) : m_keyCode(keycode) {}

	KeyReleaseEvent() = delete;
	KeyReleaseEvent(const KeyReleaseEvent &) = default;
	KeyReleaseEvent &operator=(const KeyReleaseEvent &) = default;
	KeyReleaseEvent(KeyReleaseEvent &&) = default;
	KeyReleaseEvent &operator=(KeyReleaseEvent &&) = default;
	~KeyReleaseEvent() = default;

	static EventType GetStaticType() { return EventType::KeyReleased; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Keyboard) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "KeyRelease"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_keyCode;
		return ss.str();
	}


private:
	KeyCode m_keyCode;
};

class KeyTypeEvent final : public Event
{
public:
	explicit KeyTypeEvent(const KeyCode keycode) : m_keyCode(keycode) {}

	KeyTypeEvent() = delete;
	KeyTypeEvent(const KeyTypeEvent &) = default;
	KeyTypeEvent &operator=(const KeyTypeEvent &) = default;
	KeyTypeEvent(KeyTypeEvent &&) = default;
	KeyTypeEvent &operator=(KeyTypeEvent &&) = default;
	~KeyTypeEvent() = default;

	static EventType GetStaticType() { return EventType::KeyTyped; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Keyboard) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "KeyType"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_keyCode;
		return ss.str();
	}

private:
	KeyCode m_keyCode;
};

} // namespace Hina
