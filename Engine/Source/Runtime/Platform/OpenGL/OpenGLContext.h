#pragma once

#include "Renderer/RendererContext.h"

struct GLFWwindow;

namespace Hina
{

class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow *windowHandle);

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow *m_windowHandle;
};

}// namespace Hina
