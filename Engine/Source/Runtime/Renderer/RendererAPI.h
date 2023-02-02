#pragma once

#include <glm/glm.hpp>

namespace Hina
{

class RendererAPI
{
public:
	enum class API
	{
		None = 0, OpenGL = 1
	};

	static API GetAPI() { return s_API; }

private:
	static API s_API;
};

} // namespace Hina
