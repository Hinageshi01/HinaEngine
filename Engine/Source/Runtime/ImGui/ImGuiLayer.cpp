#include "hnpch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "Application/Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hina
{

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::OnAttach() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	Application &app = Application::Get();
	GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(Event &e) {

}

void ImGuiLayer::OnUpdate() {
	ImGuiIO &io = ImGui::GetIO();
	Application &app = Application::Get();
	io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::Begin() {

}

void ImGuiLayer::End() {
	
}

void ImGuiLayer::SetDarkThemeColors() {
	
}

uint32_t ImGuiLayer::GetActiveWidgetID() const {
	return GImGui->ActiveId;
}

} // namespace Hina
