#pragma once

#include <imgui.h>
#include <imgui_internal.h>

namespace Hina
{

class ImGuiContext
{
public:
	static void Init();

private:
	static void SetDarkTheme();
};

} // namespace Hina
