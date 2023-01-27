#include "hnpch.h"

#include "WindowsWindow.h"

namespace Hina
{

static uint8_t s_GLFWWindowCount = 0;

WindowsWindow::WindowsWindow(const WindowProps &props) {
	Init(props);
}

WindowsWindow::~WindowsWindow() {
	Shutdown();
}

void WindowsWindow::Init(const WindowProps &props) {
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height; 

	 HN_CORE_INFO("Creating window {} ({}, {})", props.Title, props.Width, props.Height);

	if(s_GLFWWindowCount == 0) {
		// Init glfw when the first window create.
		int success = glfwInit();
	}

	m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	++s_GLFWWindowCount;
	
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);
}

void WindowsWindow::Shutdown() {
	glfwDestroyWindow(m_Window);
	--s_GLFWWindowCount;

	if(s_GLFWWindowCount == 0) {
		// Terminate glfw when the last window close.
		glfwTerminate();
	}
}

void WindowsWindow::OnUpdate() {
	glfwPollEvents();
}

void WindowsWindow::SetVSync(bool enabled) {
	if(enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

} // namespace Hina
