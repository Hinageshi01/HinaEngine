#include "hnpch.h"

#include "Application/Application.h"
#include "ImGuiLayer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "Platform/GLFW/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "ImGui/ImGuiLog.h"

namespace Hina
{

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

void ImGuiLayer::OnAttach() {
	GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::OnDetach() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(Event &e) {

}

void ImGuiLayer::BeginOfFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::OnImGuiRender() {
	static bool show = true;

	ImGuiLog::Get()->AddSpdLog(Log::GetSpdOutput());
	ImGuiLog::Get()->Draw("Log:", &show);

	ImGui::ShowDemoWindow(&show);
}

void ImGuiLayer::EndOfFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO &io = ImGui::GetIO();
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow *backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	 }
}

void ImGuiLayer::SetDarkThemeColors() {
	
}

uint32_t ImGuiLayer::GetActiveWidgetID() const {
	return GImGui->ActiveId;
}

} // namespace Hina
