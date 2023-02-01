#include "hnpch.h"

#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hina
{

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void *window) {
	// TODO : Need a switch here.
	return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window));

	HN_CORE_FATAL("Rendering api undefined!");
	return nullptr;
}

} // namespace Hina
