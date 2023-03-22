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

	void DrawVec3(const std::string &label, glm::vec3 &values);
	void DrawVec2(const std::string &label, float &value1, float &value2, const std::string &name1 = "", const std::string &name2 = "");

	Entity m_selectedEntity = {};
};

} // namespace Hina
