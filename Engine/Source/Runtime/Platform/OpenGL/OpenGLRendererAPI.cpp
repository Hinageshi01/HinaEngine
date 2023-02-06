#include "hnpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hina
{

void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char *message,
	const void *userParam) {
	switch(severity) {
		case GL_DEBUG_SEVERITY_HIGH:         HN_CORE_FATAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       HN_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          HN_CORE_WARN(message);  return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: HN_CORE_TRACE(message); return;
	}

	HN_CORE_ERROR("Unknown severity level!");
}

void OpenGLRendererAPI::Init() {

#ifndef NDEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

	// Depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// MSAA
	glEnable(GL_MULTISAMPLE);
	// Blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	// Line
	glEnable(GL_LINE_SMOOTH);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::SetClearDepth(const float depth) {
	glClearDepth(depth);
}

void OpenGLRendererAPI::Clear() {
	// TODO : GL_STENCIL_BUFFER_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t indexCount) {
	vertexArray->Bind();
	const uint32_t count = !!indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawLines(const std::shared_ptr<VertexArray> &vertexArray, const uint32_t vertexCount) {
	vertexArray->Bind();
	glDrawArrays(GL_LINES, 0, vertexCount);
}

void OpenGLRendererAPI::SetLineWidth(float width) {
	glLineWidth(width);
}

} // namespace Hina
