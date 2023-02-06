#pragma once

#include "Window/Window.h"
#include "Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace Hina
{

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowInitializer &init);
	virtual ~WindowsWindow();

	virtual void BeginOfFrame() override;
	virtual void OnUpdate() override;
	virtual void EndOfFrame() override;

	virtual uint32_t GetWidth() const override { return m_data.m_width; }
	virtual uint32_t GetHeight() const override { return m_data.m_height; }
	virtual float GetTime() const override { return glfwGetTime(); }

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override { return m_data.m_vsync; }

	virtual void *GetNativeWindow() const override { return m_window; }

private:
	void Init(const WindowInitializer &init);
	void Shutdown();
	void SetGLFWCallbacks();

private:
	GLFWwindow *m_window;
	std::unique_ptr<RendererContext> m_context;

	struct WindowData
	{
		std::string m_title;
		unsigned int m_width, m_height;
		bool m_vsync;

		EventCallbackFn EventCallback;
	};

	WindowData m_data;
};

}