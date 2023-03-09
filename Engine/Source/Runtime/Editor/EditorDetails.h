#pragma once

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Hina
{

class EditorDetails final
{
public:
	void OnImGuiRender();

	void SetSelection(const Entity &entity) { m_selectedEntity = entity; }

private:
	void DrawComponents();

	void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float columnWidth = 95.0f);

	Entity m_selectedEntity = {};
};

} // namespace Hina
