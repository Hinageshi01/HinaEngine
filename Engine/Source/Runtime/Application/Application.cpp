#include "hnpch.h"

#include "Application.h"
#include "Event/ApplicationEvent.h"

// tmp
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hina
{

Application::Application() {
	m_window = Window::Create();
	m_isRunning = true;
}

Application::~Application() {

}

void Application::Run() {
	while(m_isRunning) {
		m_window->OnUpdate();
	}
}

} // namespace Hina
