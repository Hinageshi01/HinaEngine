#include "hnpch.h"
#include "ImGui_GLFW_OpenGL.h"

#include "Platform/ImGui/ImGuiContext.h"

#include "Platform/ImGui/Backend/imgui_impl_glfw.h"
#include "Platform/ImGui/Backend/imgui_impl_opengl3.h"

#include "Application/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

ImGui_GLFW_OpenGL::ImGui_GLFW_OpenGL() {
	Init();
}

ImGui_GLFW_OpenGL::~ImGui_GLFW_OpenGL() {
	Shutdown();
}

void ImGui_GLFW_OpenGL::Init() {
	HN_PROFILE_FUNCTION();

	ImGuiContext::Init();

	{
		HN_PROFILE_SCOPE("ImGui backend Init");
		GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}
}

void ImGui_GLFW_OpenGL::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGui_GLFW_OpenGL::Begin() {
	HN_PROFILE_FUNCTION();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGui_GLFW_OpenGL::End() {
	HN_PROFILE_FUNCTION();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO &io = ImGui::GetIO();
	Window &window = Application::Get().GetWindow();

	io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupCurrentContext);
	}
}

uint32_t ImGui_GLFW_OpenGL::GetActiveWidgetID() {
	return GImGui->ActiveId;
}

} // namespace Hina
