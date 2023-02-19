#pragma once

#include "Window/Window.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "ImGui/ImGuiContext.h"
#include "Layer/LayerStack.h"
#include "RenderCore/Framebuffer.h"

namespace Hina
{

// Application is a singleton.
class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event &e);

	void PushLayer(Layer * layer);
	void PushOverlay(Layer * layer);

	static Application &Get() { return *m_instance; }
	Window &GetWindow() { return *m_window; }

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

	static Application *m_instance;

	std::unique_ptr<Window> m_window;
	std::unique_ptr<ImGuiContext> m_imgui;
	LayerStack m_layerStack;
	
	std::shared_ptr<Framebuffer> m_sceneFramebuffer;

	bool m_isRunning = false;
	bool m_isMinimized = false;
	float m_lastFrameTime = 0.0f;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
