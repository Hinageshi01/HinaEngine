#pragma once

#include "Event/Event.h"
#include "Core/MouseCodes.h"

namespace Hina
{

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float x, const float y)
		: m_positionX(x), m_positionY(y) {}
	MouseMovedEvent() = delete;
	MouseMovedEvent(const MouseMovedEvent &) = default;
	MouseMovedEvent &operator=(const MouseMovedEvent &) = default;
	MouseMovedEvent(MouseMovedEvent &&) = default;
	MouseMovedEvent &operator=(MouseMovedEvent &&) = default;
	~MouseMovedEvent() = default;

	float GetX() const { return m_positionX; }
	float GetY() const { return m_positionY; }

	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_positionX << ", " << m_positionY;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::MouseMoved; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "MouseMoved"; }
	virtual EVT_CAT_TYP GetCategoryFlags() const override {
		return static_cast<EVT_CAT_TYP>(EventCategory::Mouse) |
			static_cast<EVT_CAT_TYP>(EventCategory::Input);
	}

private:
	float m_positionX, m_positionY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(const float x, const float y)
		: m_offsetX(x), m_offsetY(y) {}
	MouseScrolledEvent() = delete;
	MouseScrolledEvent(const MouseScrolledEvent &) = default;
	MouseScrolledEvent &operator=(const MouseScrolledEvent &) = default;
	MouseScrolledEvent(MouseScrolledEvent &&) = default;
	MouseScrolledEvent &operator=(MouseScrolledEvent &&) = default;
	~MouseScrolledEvent() = default;

	float GetXOffset() const { return m_offsetX; }
	float GetYOffset() const { return m_offsetY; }

	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::MouseScrolled; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "MouseScrolled"; }
	virtual EVT_CAT_TYP GetCategoryFlags() const override {
		return static_cast<EVT_CAT_TYP>(EventCategory::Mouse) |
			static_cast<EVT_CAT_TYP>(EventCategory::Input);
	}

private:
	float m_offsetX, m_offsetY;
};

class MouseButtonEvent : public Event
{
public:
	MouseButtonEvent() = delete;
	MouseButtonEvent(const MouseButtonEvent &) = default;
	MouseButtonEvent &operator=(const MouseButtonEvent &) = default;
	MouseButtonEvent(MouseButtonEvent &&) = default;
	MouseButtonEvent &operator=(MouseButtonEvent &&) = default;
	~MouseButtonEvent() = default;

	MouseCode GetMouseButton() const { return m_button; }

	virtual EVT_CAT_TYP GetCategoryFlags() const override {
		return static_cast<EVT_CAT_TYP>(EventCategory::Mouse) |
			static_cast<EVT_CAT_TYP>(EventCategory::Input) |
			static_cast<EVT_CAT_TYP>(EventCategory::MouseButton);
	}

protected:
	MouseButtonEvent(const MouseCode button) : m_button(button) {}

	MouseCode m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {}
	MouseButtonPressedEvent() = delete;
	MouseButtonPressedEvent(const MouseButtonPressedEvent &) = default;
	MouseButtonPressedEvent &operator=(const MouseButtonPressedEvent &) = default;
	MouseButtonPressedEvent(MouseButtonPressedEvent &&) = default;
	MouseButtonPressedEvent &operator=(MouseButtonPressedEvent &&) = default;
	~MouseButtonPressedEvent() = default;

	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_button;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::MouseButtonPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "MouseButtonPressed"; }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}
	MouseButtonReleasedEvent() = delete;
	MouseButtonReleasedEvent(const MouseButtonReleasedEvent &) = default;
	MouseButtonReleasedEvent &operator=(const MouseButtonReleasedEvent &) = default;
	MouseButtonReleasedEvent(MouseButtonReleasedEvent &&) = default;
	MouseButtonReleasedEvent &operator=(MouseButtonReleasedEvent &&) = default;
	~MouseButtonReleasedEvent() = default;

	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_button;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::MouseButtonReleased; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual const char *GetName() const override { return "MouseButtonReleased"; }
};

} // namespace Hina
