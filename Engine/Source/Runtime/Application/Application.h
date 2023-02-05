#pragma once

#include "Core/Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Layer/LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

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

	void PushLater(Layer * layer);
	void PushOverlay(Layer * layer);

	static Application &Get() { return *s_instance; }
	Window &GetWindow() { return *m_window; }

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

	std::unique_ptr<Window> m_window;
	ImGuiLayer *m_imguiLayer;
	LayerStack m_layerStack;

	bool m_isRunning = false;

	static Application *s_instance;

	// tmp
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<VertexArray> m_vertexArray;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
