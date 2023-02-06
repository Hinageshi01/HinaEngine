#include "hnpch.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_windowHandle(windowHandle) {
	HN_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
	HN_CORE_INFO("Initializing OpenGL context");

	glfwMakeContextCurrent(m_windowHandle);

	uint8_t gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HN_CORE_ASSERT(gladSuccess, "Failed to initialize Glad!");

	glEnable(GL_MULTISAMPLE);

	HN_CORE_INFO("OpenGL Info:");
	HN_CORE_TRACE("    Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	HN_CORE_TRACE("    Renderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	HN_CORE_TRACE("    Version: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

	// It's just too long.
	// HN_CORE_INFO("  Extensions: {0}", reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS)));

	HN_CORE_ASSERT(GLVersion.major > 3 || (GLVersion.major == 3 && GLVersion.minor >= 3), "Hina requires at least OpenGL version 3.3!");
}

void OpenGLContext::SwapBuffers() {
	glfwSwapBuffers(m_windowHandle);
}

} // namespace Hina
