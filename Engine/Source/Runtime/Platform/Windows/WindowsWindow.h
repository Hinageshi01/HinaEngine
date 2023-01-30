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

	void BeginOfFrame() override;
	void OnUpdate() override;
	void EndOfFrame() override;

	unsigned int GetWidth() const override { return m_data.Width; }
	unsigned int GetHeight() const override { return m_data.Height; }

	// Window attributes.
	void SetEventCallback(const EventCallbackFn &callback) override;
	void SetVSync(bool enabled) override;
	bool IsVSync() const override { return m_data.VSync; }

	void *GetNativeWindow() const override { return m_window; }

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