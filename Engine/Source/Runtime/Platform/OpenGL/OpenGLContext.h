#pragma once

#include "RenderCore/RenderContext.h"

struct GLFWwindow;

namespace Hina
{

class OpenGLContext final : public RenderContext
{
public:
	explicit OpenGLContext(GLFWwindow *windowHandle);
	
	OpenGLContext() = delete;
	OpenGLContext(const OpenGLContext &) = default;
	OpenGLContext &operator=(const OpenGLContext &) = default;
	OpenGLContext(OpenGLContext &&) = default;
	OpenGLContext &operator=(OpenGLContext &&) = default;
	~OpenGLContext() = default;

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow *m_windowHandle;
};

}// namespace Hina
