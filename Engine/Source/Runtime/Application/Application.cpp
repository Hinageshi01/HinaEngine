#include "hnpch.h"
#include "Application.h"

#include "Core/DeltaTime.h"
#include "RenderCore/RenderCore.h"
#include "RenderCore/RenderCommand.h"
#include "Path/Path.h"

namespace Hina
{

Application *Application::s_instance = nullptr;

Application::Application() {
	assert(!s_instance && "Application instance already exist.");
	s_instance = this;

	Hina::Log::Init();
	HN_CORE_INFO("Initialized Log");
	HN_CORE_TRACE("Engine root path at: {0}", Path::FromRoot(""));

	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	m_imguiLayer = Hina::ImGuiLayer::Creat();
	PushOverlay(m_imguiLayer);

	RenderCore::Init();

	m_isRunning = true;
}

Application::~Application() {

}

void Application::PushLater(Layer *layer) {
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
	m_layerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::Run() {
	while(m_isRunning) {
		const float crtFrameTime = m_window->GetTime();
		const DeltaTime deltaTime = crtFrameTime - m_lastFrameTime;
		m_lastFrameTime = crtFrameTime;

		m_window->BeginOfFrame();

		if(!m_isMinimized) {
			m_window->OnUpdate();
			for(Layer *layer : m_layerStack) {
				layer->OnUpdate(deltaTime);
			}

			m_imguiLayer->Begin();
			for(Layer *layer : m_layerStack) {
				layer->OnImGuiRender();
			}
			m_imguiLayer->End();
		}

		m_window->EndOfFrame();
	}
}

void Application::OnEvent(Event &event) {
	HN_CORE_TRACE(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

	for(auto it = m_layerStack.end(); it != m_layerStack.begin(); /**/) {
		// Handel event by layer from high layer to low layer.
		// Example: if a click event be handled by UI layer,
		// it won't influence any layer behined UI.
		(*--it)->OnEvent(event);
		if(event.m_isHandled) {
			break;
		}
	}
}

bool Application::OnWindowClose(WindowCloseEvent &event) {
	m_isRunning = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent &event) {
	if(event.GetWidth() == 0 || event.GetHeight() == 0) {
		m_isMinimized = true;
		return false;
	}

	RenderCore::OnWindowResize(event.GetWidth(), event.GetHeight());
	return true;
}

} // namespace Hina
