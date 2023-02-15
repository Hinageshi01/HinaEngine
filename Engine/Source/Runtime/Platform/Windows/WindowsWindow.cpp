#include "hnpch.h"
#include "WindowsWindow.h"

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace Hina
{

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char *description) {
	HN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

WindowsWindow::WindowsWindow(const WindowInitializer &init) {
	Init(init);
}

WindowsWindow::~WindowsWindow() {
	Shutdown();
}

void WindowsWindow::Init(const WindowInitializer &init) {
	HN_PROFILE_FUNCTION();

	HN_CORE_INFO("Creating window {0}: ({1}, {2})", init.m_title, init.m_width, init.m_height);
	
	m_data.m_title = init.m_title;
	m_data.m_width = init.m_width;
	m_data.m_height = init.m_height; 

	if(s_GLFWWindowCount == 0) {
		// Init glfw when the first window create.
		{
			HN_PROFILE_SCOPE("int glfwInit(void)");
			uint8_t glfwSuccess = glfwInit();
			HN_CORE_ASSERT(glfwSuccess, "Failed to initialize glfw.");
		}
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, init.m_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, init.m_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(init.m_samples != 0) {
		glfwWindowHint(GLFW_SAMPLES, init.m_samples);
	}

	{
		HN_PROFILE_SCOPE("GLFWwindow* glfwCreateWindow(int width, int height, const char *title, GLFWmonitor * monitor, GLFWwindow * share)");
		m_window = glfwCreateWindow(static_cast<int>(init.m_width), static_cast<int>(init.m_height),
			m_data.m_title.c_str(), nullptr, nullptr);
		HN_CORE_ASSERT(m_window, "Failed to creating glfw windows.");
	}

	m_context = RenderContext::Create(m_window);

	glfwSetWindowUserPointer(m_window, &m_data);

	SetVSync(false);
	SetGLFWCallbacks();

	++s_GLFWWindowCount;
}

void WindowsWindow::Shutdown() {
	HN_PROFILE_FUNCTION();

	--s_GLFWWindowCount;

	{
		HN_PROFILE_SCOPE("void glfwDestroyWindow(GLFWwindow* handle)");
		glfwDestroyWindow(m_window);
	}

	if(s_GLFWWindowCount == 0) {
		HN_PROFILE_SCOPE("void glfwTerminate(void)");

		// Terminate glfw when the last window close.
		glfwTerminate();
	}
}

void WindowsWindow::EndOfFrame() {
	HN_PROFILE_FUNCTION();

	m_context->SwapBuffers();

	{
		HN_PROFILE_SCOPE("void glfwPollEvents(void)");
		glfwPollEvents();
	}

	if(Input::IsKeyPressed(Key::Escape)) {
		WindowCloseEvent event;
		m_data.EventCallback(event);
	}
}

void WindowsWindow::SetVSync(bool enabled) {
	glfwSwapInterval(enabled ? 1 : 0);
	m_data.m_vsync = enabled;
}

void WindowsWindow::SetEventCallback(const EventCallbackFn &callback) {
	m_data.EventCallback = callback;
}

void WindowsWindow::SetGLFWCallbacks() {
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
		data.m_width = width;
		data.m_height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		switch(action) {
			case GLFW_PRESS:
			{
				KeyPressEvent event(key, false);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleaseEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressEvent event(key, true);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int keycode) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		KeyTypeEvent event(keycode);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		switch(action) {
			case GLFW_PRESS:
			{
				MouseButtonPressEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseScrollEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseMoveEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
		data.EventCallback(event);
	});
}

} // namespace Hina
