#include "hnpch.h"

#include "Application/Application.h"
#include "ImGuiLayer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

namespace Hina
{

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::OnAttach() {
	Application &app = Application::Get();
	GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::OnDetach() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(Event &e) {

}

void ImGuiLayer::OnUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiIO &io = ImGui::GetIO(); (void)io;
	Application &app = Application::Get();
	GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

	io.DisplaySize = ImVec2(
		static_cast<float>(app.GetWindow().GetWidth()),
		static_cast<float>(app.GetWindow().GetHeight()));

	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

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
