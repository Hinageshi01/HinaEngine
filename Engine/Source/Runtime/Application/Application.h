#pragma once

#include "Window/Window.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Editor/EditorContext.h"
#include "Layer/LayerStack.h"
#include "RenderCore/Framebuffer.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Hina
{

// Application is a singleton.
class Application
{
public:
	Application();
	virtual ~Application();

	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	Application(Application &&) = delete;
	Application &operator=(Application &&) = delete;

	void Run();

	void OnEvent(Event &event);

	void PushLayer(Layer *layer);
	void PushOverlay(Layer *layer);

	static Application &Get() { return *m_instance; }

	Window &GetWindow() { return *m_window; }
	const Window &GetWindow() const { return *m_window; }

	Scene &GetScene() { return m_scene; }
	const Scene &GetScene() const { return m_scene; }

private:
	static Application *m_instance;

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

	std::unique_ptr<Window> m_window;
	std::unique_ptr<EditorContext> m_editorContext;
	
	std::shared_ptr<Framebuffer> m_sceneFramebuffer;

	LayerStack m_layerStack;
	Scene m_scene;

	bool m_isRunning = false;
	bool m_isMinimized = false;
	float m_lastFrameTime = 0.0f;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
