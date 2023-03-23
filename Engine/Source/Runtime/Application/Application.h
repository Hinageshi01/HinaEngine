#pragma once

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Camera/Camera.h"
#include "Core/Initializer.h"
#include "Editor/EditorContext.h"
#include "Layer/LayerStack.h"
#include "RenderCore/Framebuffer.h"
#include "Window/Window.h"

#include "Scene/Entity.h"
#include "Scene/Scene.h"

namespace Hina
{

// Application is a singleton.
class Application
{
public:
	static Application &Get() { return *m_instance; }

public:
	Application();
	virtual ~Application();

	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	Application(Application &&) = delete;
	Application &operator=(Application &&) = delete;

	void Init(const Initializer &init);
	void Run();
	void OnEvent(Event &event);
	void PushLayer(Layer *layer);
	void PushOverlay(Layer *layer);

	Window &GetWindow() { return *m_window; }
	const Window &GetWindow() const { return *m_window; }

	Scene &GetScene() { return m_scene; }
	const Scene &GetScene() const { return m_scene; }

	Framebuffer &GetPrimaryFramebuffer() { return *m_primaryFramebuffer; }
	const Framebuffer &GetPrimaryFramebuffer() const { return *m_primaryFramebuffer; }
	
	template<class T>
	void SetCameraController(T &controller) {
		controller.SetCamera(m_pCamera);
	}

	Camera &GetPrimaryCamera() { return *m_pCamera; }
	const Camera &GetPrimaryCamera() const { return *m_pCamera; }

	uint32_t GetPrimaryFramebufferColorAttachmentRenderID() const;
	void OnPrimaryFramebufferResize(const float width, const float height);

private:
	static Application *m_instance;

private:
	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

	std::shared_ptr<Camera> m_pCamera;

	std::unique_ptr<Window> m_window;
	std::unique_ptr<EditorContext> m_editorContext;
	std::unique_ptr<Framebuffer> m_primaryFramebuffer;

	Scene m_scene;
	LayerStack m_layerStack;

	bool m_isRunning = false;
	bool m_isMinimized = false;
	float m_lastFrameTime = 0.0f;
};

// To be defined in example.
Application *CreateApplication();

} // namespace Hina
