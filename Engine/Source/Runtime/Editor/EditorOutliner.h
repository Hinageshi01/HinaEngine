#pragma once

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Hina
{

class EditorOutliner final
{
public:
	EditorOutliner() = default;
	EditorOutliner(const EditorOutliner &) = default;
	EditorOutliner &operator=(const EditorOutliner &) = default;
	EditorOutliner(EditorOutliner &&) = default;
	EditorOutliner &operator=(EditorOutliner &&) = default;
	~EditorOutliner() = default;

	void OnImGuiRender();

	Entity GetSelection() { return m_selectedEntity; }
	const Entity GetSelection() const { return m_selectedEntity; }

private:
	void DrawEntityNode(Entity entity);

	Entity m_selectedEntity = {};
};

} // namespace Hina
