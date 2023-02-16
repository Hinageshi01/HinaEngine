#pragma once

#include "Event/Event.h"

#include "Core/MouseCodes.h"

namespace Hina
{

////////////////////////////// Mouse Move Event //////////////////////////////

class MouseMoveEvent final : public Event
{
public:
	MouseMoveEvent(const float x, const float y)
		: m_positionX(x), m_positionY(y) {}

	MouseMoveEvent() = delete;
	MouseMoveEvent(const MouseMoveEvent &) = default;
	MouseMoveEvent &operator=(const MouseMoveEvent &) = default;
	MouseMoveEvent(MouseMoveEvent &&) = default;
	MouseMoveEvent &operator=(MouseMoveEvent &&) = default;
	~MouseMoveEvent() = default;

	float GetX() const { return m_positionX; }
	float GetY() const { return m_positionY; }

	static EventType GetStaticType() { return EventType::MouseMoved; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Mouse) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "MouseMove"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_positionX << ", " << m_positionY;
		return ss.str();
	}


private:
	float m_positionX, m_positionY;
};

////////////////////////////// Mouse Scroll Event //////////////////////////////

class MouseScrollEvent final : public Event
{
public:
	MouseScrollEvent(const float x, const float y)
		: m_offsetX(x), m_offsetY(y) {}

	MouseScrollEvent() = delete;
	MouseScrollEvent(const MouseScrollEvent &) = default;
	MouseScrollEvent &operator=(const MouseScrollEvent &) = default;
	MouseScrollEvent(MouseScrollEvent &&) = default;
	MouseScrollEvent &operator=(MouseScrollEvent &&) = default;
	~MouseScrollEvent() = default;

	float GetXOffset() const { return m_offsetX; }
	float GetYOffset() const { return m_offsetY; }

	static EventType GetStaticType() { return EventType::MouseScrolled; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Mouse) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "MouseScroll"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_offsetX << ", " << m_offsetY;
		return ss.str();
	}
	
private:
	float m_offsetX, m_offsetY;
};

////////////////////////////// Mouse Button Event //////////////////////////////

class MouseButtonPressEvent final : public Event
{
public:
	explicit MouseButtonPressEvent(const MouseCode button) : m_button(button) {}

	MouseButtonPressEvent() = delete;
	MouseButtonPressEvent(const MouseButtonPressEvent &) = default;
	MouseButtonPressEvent &operator=(const MouseButtonPressEvent &) = default;
	MouseButtonPressEvent(MouseButtonPressEvent &&) = default;
	MouseButtonPressEvent &operator=(MouseButtonPressEvent &&) = default;
	~MouseButtonPressEvent() = default;

	static EventType GetStaticType() { return EventType::MouseButtonPressed; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::MouseButton) |
			static_cast<uint8_t>(EventCategory::Mouse) |
			static_cast<uint8_t>(EventCategory::Input);
	}

	virtual const char *GetName() const override { return "MouseButtonPress"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_button;
		return ss.str();
	}
	
private:
	MouseCode m_button;
};

class MouseButtonReleaseEvent final : public Event
{
public:
	explicit MouseButtonReleaseEvent(const MouseCode button) : m_button(button) {}

	MouseButtonReleaseEvent() = delete;
	MouseButtonReleaseEvent(const MouseButtonReleaseEvent &) = default;
	MouseButtonReleaseEvent &operator=(const MouseButtonReleaseEvent &) = default;
	MouseButtonReleaseEvent(MouseButtonReleaseEvent &&) = default;
	MouseButtonReleaseEvent &operator=(MouseButtonReleaseEvent &&) = default;
	~MouseButtonReleaseEvent() = default;

	static EventType GetStaticType() { return EventType::MouseButtonReleased; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual uint8_t GetCategoryFlags() const override {
		return static_cast<uint8_t>(EventCategory::Input) |
			static_cast<uint8_t>(EventCategory::Mouse) |
			static_cast<uint8_t>(EventCategory::MouseButton);
	}

	virtual const char *GetName() const override { return "MouseButtonRelease"; }
	virtual std::string ToString() const override {
		std::stringstream ss;
		ss << GetName() << ": " << m_button;
		return ss.str();
	}

private:
	MouseCode m_button;
};

} // namespace Hina
