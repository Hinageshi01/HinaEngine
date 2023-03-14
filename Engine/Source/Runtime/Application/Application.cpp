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

	assert(!m_instance && "Application instance already exist.");
	m_instance = this;

	RenderCore::SetAPI(GraphicsAPI::OpenGL);

	m_window = Window::Create();
	m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	RenderCore::Init();

	m_editorContext = EditorContext::Creat();

	FramebufferInitializer framebufferInit;
	framebufferInit.m_width = RenderCore::GetWidth();
	framebufferInit.m_height = RenderCore::GetHeight();
	framebufferInit.m_attachmentFormats = { FramebufferFormat::RGBA8, FramebufferFormat::DEPTH24STENCIL8 };
	m_primaryFramebuffer = Framebuffer::Create(framebufferInit);

	PushLayer(new EditorLayer());

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

uint32_t Application::GetPrimaryFramebufferColorAttachmentRenderID() const {
	return m_primaryFramebuffer->GetColorAttachmentRenderID();
}

void Application::OnPrimaryFramebufferResize(float width, float height) {
	m_primaryFramebuffer->Resize(width, height);
}

} // namespace Hina
