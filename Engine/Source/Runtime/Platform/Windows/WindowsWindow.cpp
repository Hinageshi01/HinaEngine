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

WindowsWindow::WindowsWindow(const WindowProps &props) {
	Init(props);
}

WindowsWindow::~WindowsWindow() {
	Shutdown();
}

void WindowsWindow::Init(const WindowProps &props) {
	m_data.Title = props.Title;
	m_data.Width = props.m_width;
	m_data.Height = props.m_height; 

	HN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.m_width, props.m_height);

	if(s_GLFWWindowCount == 0) {
		// Init glfw when the first window create.
		uint8_t glfwSuccess = glfwInit();
		HN_CORE_ASSERT(glfwSuccess, "Failed to initialize glfw.");
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	m_window = glfwCreateWindow(static_cast<int>(props.m_width), static_cast<int>(props.m_height),
		m_data.Title.c_str(), nullptr, nullptr);
	HN_CORE_ASSERT(m_window, "Failed to creating glfw windows.");

	++s_GLFWWindowCount;
	
	m_context = GraphicsContext::Create(m_window);
	m_context->Init();

	glfwSetWindowUserPointer(m_window, &m_data);

	SetVSync(true);
	SetGLFWCallbacks();
}

void WindowsWindow::Shutdown() {
	glfwDestroyWindow(m_window);
	--s_GLFWWindowCount;

	if(s_GLFWWindowCount == 0) {
		// Terminate glfw when the last window close.
		glfwTerminate();
	}
}

void WindowsWindow::BeginOfFrame() {
	// TODO : Window should not use any specific rendering api code.
	glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WindowsWindow::OnUpdate() {

}

void WindowsWindow::EndOfFrame() {
	glfwPollEvents();
	m_context->SwapBuffers();

	if(Input::IsKeyPressed(Key::Escape)) {
		WindowCloseEvent event;
		m_data.EventCallback(event);
	}
}

void WindowsWindow::SetVSync(bool enabled) {
	glfwSwapInterval(enabled ? 1 : 0);
	m_data.VSync = enabled;
}

void WindowsWindow::SetEventCallback(const EventCallbackFn &callback) {
	m_data.EventCallback = callback;
}

void WindowsWindow::SetGLFWCallbacks() {
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

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
				KeyPressedEvent event(key, false);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int keycode) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		switch(action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
		WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

		MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
		data.EventCallback(event);
	});
}

} // namespace Hina
