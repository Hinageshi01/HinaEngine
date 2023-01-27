#include "hnpch.h"

#include "Application.h"

namespace Hina
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() {
	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	m_isRunning = true;
}

Application::~Application() {

}

void Application::Run() {
	while(m_isRunning) {
		m_window->OnUpdate();
	}
}

void Application::OnEvent(Event &e) {
	HN_CORE_TRACE(e);

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
	m_isRunning = false;
	return true;
}

} // namespace Hina
