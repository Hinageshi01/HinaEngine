#pragma once

#include "ImGui/ImGuiContext.h"

namespace Hina
{

class ImGuiContext_GLFW_OpenGL final : public ImGuiContext
{
public:
	ImGuiContext_GLFW_OpenGL() = default;
	ImGuiContext_GLFW_OpenGL(const ImGuiContext_GLFW_OpenGL &) = default;
	ImGuiContext_GLFW_OpenGL &operator=(const ImGuiContext_GLFW_OpenGL &) = default;
	ImGuiContext_GLFW_OpenGL(ImGuiContext_GLFW_OpenGL &&) = default;
	ImGuiContext_GLFW_OpenGL &operator=(ImGuiContext_GLFW_OpenGL &&) = default;
	virtual ~ImGuiContext_GLFW_OpenGL();

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void Begin() override;
	virtual void End() override;

	virtual void SetDarkTheme() override;

	virtual uint32_t GetActiveWidgetID() override;
};

} // namespace Hina
