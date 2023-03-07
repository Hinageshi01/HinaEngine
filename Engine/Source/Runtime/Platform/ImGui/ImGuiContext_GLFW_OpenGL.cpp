#include "hnpch.h"
#include "ImGuiContext_GLFW_OpenGL.h"

#include "Platform/ImGui/Backend/imgui_impl_glfw.h"
#include "Platform/ImGui/Backend/imgui_impl_opengl3.h"

#include "Application/Application.h"
#include "Icon/IconsFontAwesome6.h"
#include "Path/Path.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Hina
{

ImGuiContext_GLFW_OpenGL::ImGuiContext_GLFW_OpenGL() {
	Init();
}

ImGuiContext_GLFW_OpenGL::~ImGuiContext_GLFW_OpenGL() {
	Shutdown();
}

void ImGuiContext_GLFW_OpenGL::Init() {
	HN_PROFILE_FUNCTION();

	IMGUI_CHECKVERSION();

	{
		HN_PROFILE_SCOPE("ImGuiContext* ImGui::CreateContext(ImFontAtlas*)");
		ImGui::CreateContext();
	}

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	{
		HN_PROFILE_SCOPE("ImGui load Font");
		io.Fonts->AddFontFromFileTTF(Path::FromAsset("Font/DroidSans.ttf").c_str(), 16.0f);
	}

	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 16.0f;
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	{
		HN_PROFILE_SCOPE("ImGui load Icon");
		io.Fonts->AddFontFromFileTTF(Path::FromAsset("Icon/fa-solid-900.ttf").c_str(), 13.0f, &config, icon_ranges);
	}

	// When viewports are enabled we tweak WindowRounding/WindowBg,
	// so platform windows can look identical to regular ones.
	ImGuiStyle &style = ImGui::GetStyle();
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui::StyleColorsDark();
	SetDarkTheme();

	{
		HN_PROFILE_SCOPE("ImGui backend Init");
		GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}
}

void ImGuiContext_GLFW_OpenGL::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiContext_GLFW_OpenGL::Begin() {
	HN_PROFILE_FUNCTION();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiContext_GLFW_OpenGL::End() {
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

void ImGuiContext_GLFW_OpenGL::SetDarkTheme() {
	auto &colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

uint32_t ImGuiContext_GLFW_OpenGL::GetActiveWidgetID() {
	return GImGui->ActiveId;
}

} // namespace Hina
