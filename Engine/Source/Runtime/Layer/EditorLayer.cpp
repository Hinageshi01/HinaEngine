#include "hnpch.h"
#include "EditorLayer.h"

#include "Application/Application.h"
#include "RenderCore/RenderCore.h"

namespace Hina
{

namespace
{
constexpr ImGuiWindowFlags EDITOR_FLAG = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
	ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
}

void EditorLayer::OnAttach() {

}

void EditorLayer::OnDetach() {

}

void EditorLayer::Begin() {

}

void EditorLayer::OnUpdate(const DeltaTime deltaTime) {

}

void EditorLayer::End() {

}

void EditorLayer::OnImGuiRender() {
	HN_PROFILE_FUNCTION();

	ShowDockSpace();
	ShowScene();

	ShowProfiler();

	ShowOutLiner();
	SetSelectedEntity();
	ShowDetails();

	ShowLog();
}

void EditorLayer::OnEvent(Event &event) {

}

void EditorLayer::ShowDockSpace() {
	HN_PROFILE_FUNCTION();

	static ImGuiDockNodeFlags dockspaceFlag = ImGuiDockNodeFlags_AutoHideTabBar;

	const ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, EDITOR_FLAG);
	ImGui::PopStyleVar(3);

	// Submit the DockSpace
	ImGuiIO &io = ImGui::GetIO();
	if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspaceID = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlag);
	}

	if(ImGui::BeginMenuBar()) {
		if(ImGui::BeginMenu("Options")) {
			if(ImGui::MenuItem("NoResize", "", (dockspaceFlag & ImGuiDockNodeFlags_NoResize) != 0)) {
				dockspaceFlag ^= ImGuiDockNodeFlags_NoResize;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::End();
}

void EditorLayer::ShowScene() {
	HN_PROFILE_FUNCTION();

	ImGui::Begin("Scene");

	ImGui::Image((void *)(uint64_t)RenderCore::GetFramebufferColorAttachmentRenderID(),
		ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

	glm::vec2 crtSceneSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };
	if(m_primaryFramebufferSize != crtSceneSize) {
		m_primaryFramebufferSize = std::move(crtSceneSize);

		RenderCore::OnFrameResize(static_cast<uint32_t>(m_primaryFramebufferSize.x),
								  static_cast<uint32_t>(m_primaryFramebufferSize.y));
	}

	ImGui::End();
}

void EditorLayer::ShowDetails() {
	HN_PROFILE_FUNCTION();

	m_detaills.OnImGuiRender();
}

void EditorLayer::ShowLog() {
	HN_PROFILE_FUNCTION();

	m_log.AddSpdLog(Hina::Log::GetSpdOutput());
	m_log.OnImGuiRender();
}

void EditorLayer::ShowOutLiner() {
	m_outliner.OnImGuiRender();
}

void EditorLayer::ShowProfiler() {
	m_profiler.OnImGuiRender();
}

void EditorLayer::SetSelectedEntity() {
	m_detaills.SetSelection(m_outliner.GetSelection());
}

} //namespace Hina
