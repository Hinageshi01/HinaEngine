#pragma once

#include "Core/DeltaTime.h"
#include "Event/Event.h"

namespace Hina
{

class Layer
{
public:
	Layer(const std::string &name = "Layer");
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	virtual void Begin() {}
	virtual void OnUpdate(const DeltaTime deltaTime) {}
	virtual void End() {}

	virtual void OnImGuiRender() {}
	
	virtual void OnEvent(Event &event) {}

	const std::string &GetName() const { return m_debugName; }

protected:
	std::string m_debugName;
};

} // namespace Hina

