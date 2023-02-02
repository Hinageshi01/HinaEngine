#pragma once

#include "Core/Window.h"
#include "Renderer/RendererContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hina
{

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps &props);
	virtual ~WindowsWindow();

	virtual void BeginOfFrame() override;
	virtual void OnUpdate() override;
	virtual void EndOfFrame() override;

	virtual unsigned int GetWidth() const override { return m_data.m_width; }
	virtual unsigned int GetHeight() const override { return m_data.m_height; }

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override { return m_data.m_vsync; }

	virtual void *GetNativeWindow() const override { return m_window; }

private:
	void Init(const WindowProps &props);
	void Shutdown();
	void SetGLFWCallbacks();

private:
	GLFWwindow *m_window;
	std::unique_ptr<GraphicsContext> m_context;

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