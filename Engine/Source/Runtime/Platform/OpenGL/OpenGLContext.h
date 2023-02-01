#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hina
{

class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow *windowHandle);

	virtual void Init(const uint32_t major, const uint32_t minor) override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow *m_windowHandle;
};

}// namespace Hina
