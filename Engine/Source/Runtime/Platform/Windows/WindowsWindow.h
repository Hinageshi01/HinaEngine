#pragma once

#include "Window/Window.h"
#include "RenderCore/RenderContext.h"

#include <GLFW/glfw3.h>

namespace Hina
{

class WindowsWindow final : public Window
{
public:
	explicit WindowsWindow(const WindowInitializer &init);
	
	WindowsWindow() = delete;
	WindowsWindow(const WindowsWindow &) = default;
	WindowsWindow &operator=(const WindowsWindow &) = default;
	WindowsWindow(WindowsWindow &&) = default;
	WindowsWindow &operator=(WindowsWindow &&) = default;
	virtual ~WindowsWindow();

	virtual void EndOfFrame() override;

	virtual uint32_t GetWidth() const override { return m_data.m_width; }
	virtual uint32_t GetHeight() const override { return m_data.m_height; }
	virtual float GetTime() const override { return static_cast<float>(glfwGetTime()); }

	// Window attributes.
	virtual void SetEventCallback(const EventCallbackFn &callback) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override { return m_data.m_vsync; }

	virtual void *GetNativeWindow() const override { return m_window; }

private:
	void Init(const WindowInitializer &init);
	void Shutdown();
	void SetGLFWCallbacks();

	GLFWwindow *m_window;
	std::unique_ptr<RenderContext> m_context;

	struct WindowData
	{
		std::string m_title;
		unsigned int m_width, m_height;
		bool m_vsync;

		EventCallbackFn EventCallback;
	};

	WindowData m_data;
};

} // namespace Hina
