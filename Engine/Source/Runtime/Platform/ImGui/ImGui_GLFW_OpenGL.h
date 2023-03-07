#pragma once

#include "Editor/EditorContext.h"

namespace Hina
{

class ImGui_GLFW_OpenGL final : public EditorContext
{
public:
	ImGui_GLFW_OpenGL();
	ImGui_GLFW_OpenGL(const ImGui_GLFW_OpenGL &) = default;
	ImGui_GLFW_OpenGL &operator=(const ImGui_GLFW_OpenGL &) = default;
	ImGui_GLFW_OpenGL(ImGui_GLFW_OpenGL &&) = default;
	ImGui_GLFW_OpenGL &operator=(ImGui_GLFW_OpenGL &&) = default;
	virtual ~ImGui_GLFW_OpenGL();

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void Begin() override;
	virtual void End() override;

	virtual uint32_t GetActiveWidgetID() override;
};

} // namespace Hina
