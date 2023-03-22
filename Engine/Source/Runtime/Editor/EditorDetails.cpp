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
	static constexpr ImGuiTreeNodeFlags s_treeNodeFlags = 0
		| ImGuiTreeNodeFlags_DefaultOpen
		| ImGuiTreeNodeFlags_Framed
		| ImGuiTreeNodeFlags_SpanAvailWidth
		| ImGuiTreeNodeFlags_AllowItemOverlap
		| ImGuiTreeNodeFlags_FramePadding;

	if(m_selectedEntity.HasComponent<NameComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0.5f, 0.5f });
		bool open = ImGui::TreeNodeEx((void *)typeid(NameComponent).hash_code(), s_treeNodeFlags, "Infomation");
		ImGui::PopStyleVar();
		if(open) {
			auto &name = m_selectedEntity.GetComponent<NameComponent>().GetName();

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 75.0f);
			ImGui::Text("Name :");
			ImGui::NextColumn();
			ImGui::Text(name.c_str());

			ImGui::Columns(1);
			ImGui::TreePop();
		}
	}

	if(m_selectedEntity.HasComponent<TransformComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0.5f, 0.5f });
		bool open = ImGui::TreeNodeEx((void *)typeid(TransformComponent).hash_code(), s_treeNodeFlags, "Transform");
		ImGui::PopStyleVar();
		if(open) {
			auto &component = m_selectedEntity.GetComponent<TransformComponent>();

			DrawVec3("Translation :", component.GetTranslation(), 0.0f);

			glm::vec3 rotation = glm::degrees(component.GetRotation());
			DrawVec3("Rotation :", rotation, 0.0f);
			component.SetRotation(glm::radians(rotation));

			DrawVec3("Scale :", component.GetScale(), 1.0f);

			ImGui::TreePop();
		}
	}

	if(m_selectedEntity.HasComponent<CameraComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 0.5f, 0.5f });
		bool open = ImGui::TreeNodeEx((void *)typeid(CameraComponent).hash_code(), s_treeNodeFlags, "Camera");
		ImGui::PopStyleVar();
		if(open) {
			auto &component = m_selectedEntity.GetComponent<CameraComponent>();

			DrawVec3("Position :", component.GetPosition());

			float yaw = glm::degrees(component.GetYaw());
			float pitch = glm::degrees(component.GetPitch());
			DrawVec2("Look at :", yaw, pitch, "Y", "P");
			component.SetYaw(glm::radians(yaw));
			component.SetPitch(glm::radians(pitch));

			DrawVec2("Frustum :", component.GetNear(), component.GetFar(), "N", "F");

			ImGui::TreePop();
		}
	}
}

void EditorDetails::DrawVec3(const std::string &label, glm::vec3 &values, float resetValue) {
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75.0f);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.45f, 0.45f, 0.45f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.6f, 0.6f, 0.6f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.45f, 0.45f, 0.45f, 1.0f });
	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
	ImGui::PushItemWidth(50.0f);

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight, lineHeight };

	if(ImGui::Button("X", buttonSize)) {
		values.x = resetValue;
	}
	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");

	ImGui::SameLine();
	if(ImGui::Button("Y", buttonSize)) {
		values.y = resetValue;
	}
	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
	
	ImGui::SameLine();
	if(ImGui::Button("Z", buttonSize)) {
		values.z = resetValue;
	}
	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");

	ImGui::PopItemWidth();
	ImGui::PopFont();
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
}

void EditorDetails::DrawVec2(const std::string &label,
							 float &value1, float &value2,
							 const std::string &name1, const std::string &name2,
							 float resetValue) {
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75.0f);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();
	 
	ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.45f, 0.45f, 0.45f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.6f, 0.6f, 0.6f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.45f, 0.45f, 0.45f, 1.0f });
	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
	ImGui::PushItemWidth(50.0f);

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight, lineHeight };

	if(ImGui::Button(name1.c_str(), buttonSize)) {
		value1 = resetValue;
	}
	ImGui::SameLine();
	ImGui::DragFloat("##X", &value1, 0.1f, 0.0f, 0.0f, "%.2f");
	
	ImGui::SameLine();
	if(ImGui::Button(name2.c_str(), buttonSize)) {
		value2 = resetValue;
	}
	ImGui::SameLine();
	ImGui::DragFloat("##Y", &value2, 0.1f, 0.0f, 0.0f, "%.2f");
	
	ImGui::PopItemWidth();
	ImGui::PopFont();
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
}

} // namespace Hina
