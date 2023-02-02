#pragma once

#include "Core/Window.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Layer/LayerStack.h"

#include "Platform/OpenGL/OpenGLShader.h"

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
	bool OnWindowClose(WindowCloseEvent &e);

	std::unique_ptr<Window> m_window;
	ImGuiLayer *m_imguiLayer;
	LayerStack m_layerStack;

	bool m_isRunning = false;

	static Application *s_instance;

	// tmp
	unsigned int m_VBO;
	unsigned int m_EBO;
	std::unique_ptr<GLShader> m_shader;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
