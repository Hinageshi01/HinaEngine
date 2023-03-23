#include "hnpch.h"
#include "Application.h"

#include "Core/DeltaTime.h"
#include "Layer/EditorLayer.h"
#include "RenderCore/RenderCore.h"

namespace Hina
{

Application *Application::m_instance = nullptr;

Application::Application() {
	HN_PROFILE_FUNCTION();

	assert(nullptr == m_instance && "Application instance already exist!");
	m_instance = this;
}

Application::~Application() {

}
void Application::Init(const Initializer &init) {
	m_isRunning = true;

	RenderCore::SetAPI(init.m_api);

	m_window = Window::Create(init.m_window);
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	RenderCore::Init();

	m_editorContext = EditorContext::Creat();

	m_primaryFramebuffer = Framebuffer::Create();

	m_pCamera = std::make_shared<Camera>();
	auto cameraEntitty = m_scene.CreateEntity("Primary Camera");
	cameraEntitty.AddComponent<CameraComponent>(m_pCamera);

	PushLayer(new EditorLayer());
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

				m_primaryFramebuffer->Bind();
				for(Layer *layer : m_layerStack) {
					layer->OnUpdate(deltaTime);
				}
				m_primaryFramebuffer->Unbind();
			}

			m_editorContext->Begin();
			{
				HN_PROFILE_SCOPE("ImGuiLayers Render");
				for(Layer *layer : m_layerStack) {
					layer->OnImGuiRender();
				}
			}
			m_editorContext->End();
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

void Application::PushLayer(Layer *layer) {
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
	m_layerStack.PushOverlay(layer);
	layer->OnAttach();
}

uint32_t Application::GetPrimaryFramebufferColorAttachmentRenderID() const {
	return m_primaryFramebuffer->GetColorAttachmentRenderID();
}

void Application::OnPrimaryFramebufferResize(const float width, const float height) {
	RenderCore::SetViewport(0, 0, static_cast<uint32_t>(width), static_cast<uint32_t>(height));
	m_primaryFramebuffer->Resize(width, height);
}

bool Application::OnWindowClose(WindowCloseEvent &event) {
	HN_CORE_TRACE(event);

	m_isRunning = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent &event) {
	HN_CORE_TRACE(event);

	if(event.GetWidth() == 0 || event.GetHeight() == 0) {
		m_isMinimized = true;
	}

	return false;
}

} // namespace Hina
