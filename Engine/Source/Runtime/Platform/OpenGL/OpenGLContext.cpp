#include "hnpch.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
	: m_WindowHandle(windowHandle) {
	HN_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
	glfwMakeContextCurrent(m_WindowHandle);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	uint8_t gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HN_CORE_ASSERT(gladSuccess, "Failed to initialize Glad!");

	HN_CORE_INFO("OpenGL Info:");
	HN_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	HN_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	HN_CORE_INFO("  Version: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

	HN_CORE_ASSERT(GLVersion.major > 3 || (GLVersion.major == 3 && GLVersion.minor >= 3), "Hina requires at least OpenGL version 3.3!");
}

void OpenGLContext::SwapBuffers() {
	glfwSwapBuffers(m_WindowHandle);
}

} // namespace Hina
