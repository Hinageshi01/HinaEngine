#pragma once

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "glm/glm.hpp"

namespace Hina
{

// Application is a singleton.
class Input
{
public:
	static bool IsKeyPressed(KeyCode key);

	static bool IsMouseButtonPressed(MouseCode button);

	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};

} // namespace Hina
