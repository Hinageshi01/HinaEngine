#pragma once

#include "Core/DeltaTime.h"
#include "Event/Event.h"

namespace Hina
{

class Layer
{
public:
	explicit Layer(const std::string &name = "Layer") : m_name(name) {};
	explicit Layer(std::string &&name = "Layer") : m_name(name) {};

	Layer() = default;
	Layer(const Layer &) = default;
	Layer &operator=(const Layer &) = default;
	Layer(Layer &&) = default;
	Layer &operator=(Layer &&) = default;
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	virtual void Begin() {}
	virtual void OnUpdate(const DeltaTime deltaTime) {}
	virtual void End() {}

	virtual void OnImGuiRender() {}
	
	virtual void OnEvent(Event &event) {}

	std::string &GetName() { return m_name; }
	const std::string &GetName() const { return m_name; }

protected:
	std::string m_name;
};

} // namespace Hina

