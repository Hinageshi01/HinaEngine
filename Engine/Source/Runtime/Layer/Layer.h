#pragma once

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

	virtual void BeginOfFrame() {}
	virtual void OnUpdate() {}
	virtual void EndOfFrame() {}

	virtual void OnImGuiRender() {}
	
	virtual void OnEvent(Event &event) {}

	const std::string &GetName() const { return m_DebugName; }

protected:
	std::string m_DebugName;
};

}
