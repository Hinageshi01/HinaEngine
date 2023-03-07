#pragma once

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Hina
{

class EditorHierarchy final
{
public:
	EditorHierarchy() = default;
	EditorHierarchy(const EditorHierarchy &) = default;
	EditorHierarchy &operator=(const EditorHierarchy &) = default;
	EditorHierarchy(EditorHierarchy &&) = default;
	EditorHierarchy &operator=(EditorHierarchy &&) = default;
	~EditorHierarchy() = default;

	void OnImGuiRender();

private:
	void DrawEntityNode(Entity entity);

	Entity m_selectionEntity = {};
};

} // namespace Hina
