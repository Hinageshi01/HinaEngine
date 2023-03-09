#include "hnpch.h"
#include "EditorDetails.h"

#include <glm/gtc/type_ptr.hpp>
#include <Icon/IconsFontAwesome6.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Hina
{

void EditorDetails::OnImGuiRender() {
	ImGui::Begin("Details");
	if(m_selectedEntity.IsValid()) {
		DrawComponents();
	}
	ImGui::End();
}

void EditorDetails::DrawComponents() {
	if(m_selectedEntity.HasComponent<NameComponent>()) {
		auto &name = m_selectedEntity.GetComponent<NameComponent>().name;
	
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 95.0f);
		ImGui::Text("Name :");
		ImGui::NextColumn();
	
		// char buffer[256];
		// memset(buffer, 0, sizeof(buffer));
		// strncpy_s(buffer, sizeof(buffer), name.c_str(), sizeof(buffer));
		// if(ImGui::InputText("##Name", buffer, sizeof(buffer))) {
		// 	name = std::string(buffer);
		// }

		ImGui::Text(name.c_str());

		ImGui::Columns(1);
	}

	if(m_selectedEntity.HasComponent<TransformComponent>()) {
		ImGui::Separator();

		auto &component = m_selectedEntity.GetComponent<TransformComponent>();

		DrawVec3Control("Translation :", component.translation);
		glm::vec3 rotation = glm::degrees(component.rotation);
		DrawVec3Control("Rotation :", rotation);
		component.rotation = glm::radians(rotation);
		DrawVec3Control("Scale :", component.scale, 1.0f);
	}
}

void EditorDetails::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth) {
	ImGuiIO &io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushFont(boldFont);
	if(ImGui::Button("X", buttonSize)) {
		values.x = resetValue;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushFont(boldFont);
	if(ImGui::Button("Y", buttonSize)) {
		values.y = resetValue;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushFont(boldFont);
	if(ImGui::Button("Z", buttonSize)) {
		values.z = resetValue;
	}
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
}

} // namespace Hina
