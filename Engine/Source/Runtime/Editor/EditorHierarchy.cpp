#include "hnpch.h"
#include "EditorHierarchy.h"

#include "Application/Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Hina
{

void EditorHierarchy::OnImGuiRender()
{
	ImGui::Begin("Hierarchy");
	Application::Get().GetScene().GetRegistry().each([&](auto entityID) {
		Entity entity{ entityID , &(Application::Get().GetScene())};
		DrawEntityNode(entity);
	});

	if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
		m_selectionEntity = {};
	}

	// Right-click on blank space
	if(ImGui::BeginPopupContextWindow(0, 1)) {
		if(ImGui::MenuItem("Create New Entity")) {
			Application::Get().GetScene().CreateEntity("New Entity");
		}

		ImGui::EndPopup();
	}
	ImGui::End();
}

void EditorHierarchy::DrawEntityNode(Entity entity) {
	const std::string &name = entity.GetComponent<NameComponent>().name;

	ImGuiTreeNodeFlags flags = ((m_selectionEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	bool open = ImGui::TreeNodeEx((void *)(uint64_t)entity.GetIDu32(), flags, name.c_str());

	if(ImGui::IsItemClicked()) {
		m_selectionEntity = entity;
	}

	if(open) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		ImGui::TreePop();
	}
}

} // namespace Hina
