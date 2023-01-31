#pragma once

#include "Core/Window.h"
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

	virtual unsigned int GetWidth() const override { return m_data.Width; }
	virtual unsigned int GetHeight() const override { return m_data.Height; }

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override { return m_data.VSync; }

	virtual void *GetNativeWindow() const override { return m_window; }

private:
	void Init(const WindowProps &props);
	void Shutdown();
	void SetGLFWCallbacks();

private:
	GLFWwindow *m_window;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	WindowData m_data;
};

}