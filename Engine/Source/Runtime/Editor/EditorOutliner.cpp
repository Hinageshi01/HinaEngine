#include "hnpch.h"
#include "EditorOutliner.h"

#include "Application/Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Hina
{

void EditorOutliner::OnImGuiRender()
{
	ImGui::Begin("Hierarchy");
	Application::Get().GetScene().GetRegistry().each([&](auto entityID) {
		Entity entity{ entityID , &(Application::Get().GetScene())};
		DrawEntityNode(entity);
	});

	if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
		m_selectedEntity = {};
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

void EditorOutliner::DrawEntityNode(Entity entity) {
	const std::string &name = entity.GetComponent<NameComponent>().GetName();

	ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	bool open = ImGui::TreeNodeEx((void *)(uint64_t)entity.GetIDu32(), flags, name.c_str());

	if(ImGui::IsItemClicked()) {
		m_selectedEntity = entity;
	}

	if(open) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		ImGui::TreePop();
	}
}

} // namespace Hina
