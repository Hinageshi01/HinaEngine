#include "hnpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_windowHandle(windowHandle) {
	HN_PROFILE_FUNCTION();

	Init();
}

void OpenGLContext::Init() {
	HN_PROFILE_FUNCTION();

	HN_CORE_INFO("Initializing OpenGL context");

	{
		HN_PROFILE_SCOPE("void glfwMakeContextCurrent(GLFWwindow* handle)");
		glfwMakeContextCurrent(m_windowHandle);
	}

	{
		HN_PROFILE_SCOPE("int gladLoadGLLoader(GLADloadproc load)");
		uint8_t gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		assert(gladSuccess && "Failed to initialize Glad!");
	}

	glEnable(GL_MULTISAMPLE);

	HN_CORE_TRACE("OpenGL details:");
	HN_CORE_TRACE("    Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	HN_CORE_TRACE("    Renderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	HN_CORE_TRACE("    Version: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

	HN_CORE_ASSERT(GLVersion.major > 3 || (GLVersion.major == 3 && GLVersion.minor >= 3), "Hina requires at least OpenGL version 3.3!");
}

void OpenGLContext::SwapBuffers() {
	HN_PROFILE_FUNCTION();

	glfwSwapBuffers(m_windowHandle);
}

} // namespace Hina
