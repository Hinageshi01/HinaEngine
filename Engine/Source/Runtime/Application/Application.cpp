#include "hnpch.h"
#include "Application.h"

#include "Core/DeltaTime.h"
#include "RenderCore/RenderCore.h"
#include "RenderCore/RenderCommand.h"
#include "Path/Path.h"

namespace Hina
{

Application *Application::ms_instance = nullptr;

Application::Application() {
	HN_PROFILE_FUNCTION();

	assert(!ms_instance && "Application instance already exist.");
	ms_instance = this;

	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	
	RenderCore::Init();

	m_imguiLayer = Hina::ImGuiLayer::Creat();
	PushOverlay(m_imguiLayer);

	m_isRunning = true;
}

Application::~Application() {

}

void Application::PushLayer(Layer *layer) {
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
	m_layerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::Run() {
	HN_PROFILE_FUNCTION();

	while(m_isRunning) {
		HN_PROFILE_SCOPE("[ Main Loop ]");

		const float crtFrameTime = m_window->GetTime();
		const DeltaTime deltaTime = crtFrameTime - m_lastFrameTime;
		m_lastFrameTime = crtFrameTime;

		if(!m_isMinimized) {
			{
				HN_PROFILE_SCOPE("Layers Update");
				for(Layer *layer : m_layerStack) {
					layer->OnUpdate(deltaTime);
				}
			}

			m_imguiLayer->Begin();
			{
				HN_PROFILE_SCOPE("ImGuiLayers Render");
				for(Layer *layer : m_layerStack) {
					layer->OnImGuiRender();
				}
			}
			m_imguiLayer->End();
		}

		m_window->EndOfFrame();
	}
}

void Application::OnEvent(Event &event) {
	HN_PROFILE_FUNCTION();

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
