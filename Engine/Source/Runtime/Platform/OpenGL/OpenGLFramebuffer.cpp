#include "hnpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Hina
{

namespace
{
constexpr uint16_t MAX_FRAMEBUFFER_SIZE = 8192;
}

namespace Utils
{

static inline void AttachColorTexture(uint32_t id, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, size_t index) {
	HN_PROFILE_FUNCTION();

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + index), GL_TEXTURE_2D, id, 0);
}

static inline void AttachDepthTexture(uint32_t id, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
	HN_PROFILE_FUNCTION();

	glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, id, 0);
}

static inline bool IsDepthFormat(FramebufferFormat format) {
	switch(format) {
		case FramebufferFormat::DEPTH24STENCIL8:
			return true;
	}

	return false;
}

static inline GLenum GetOpenGLTextureFormat(FramebufferFormat format) {
	switch(format) {
		case FramebufferFormat::RGBA8:
			return GL_RGBA8;

		case FramebufferFormat::RED_INTEGER:
			return GL_RED_INTEGER;
	}

	HN_CORE_ERROR("Unkonw Format!");
	return 0;
}

} // namespace Utils

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferInitializer &init)
{
	for(const auto &format : init.m_attachmentFormats) {
		if(!Utils::IsDepthFormat(format)) {
			m_colorAttachmentFormats.emplace_back(format);
		}
		else {
			m_depthAttachmentFormat = format;
		}
	}

	m_width = init.m_width;
	m_height = init.m_height;

	Invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer() {
	Delete();
}

void OpenGLFramebuffer::Invalidate() {
	HN_PROFILE_FUNCTION();

	if(m_rendererID) {
		Delete();
		m_colorAttachmentsRenderID.clear();
		m_depthAttachmentRenderID = 0;
	}

	glCreateFramebuffers(1, &m_rendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

	// Color Attachments.
	if(!m_colorAttachmentFormats.empty()) {
		m_colorAttachmentsRenderID.resize(m_colorAttachmentFormats.size());
		glCreateTextures(GL_TEXTURE_2D,
						 static_cast<GLsizei>(m_colorAttachmentsRenderID.size()),
						 static_cast<GLuint *>(m_colorAttachmentsRenderID.data()));

		for(size_t i = 0; i < m_colorAttachmentsRenderID.size(); ++i) {
			glBindTexture(GL_TEXTURE_2D, m_colorAttachmentsRenderID[i]);
			switch(m_colorAttachmentFormats[i]) {
				case FramebufferFormat::RGBA8:
					Utils::AttachColorTexture(m_colorAttachmentsRenderID[i], GL_RGBA8, GL_RGBA,
						m_width, m_height, i);
					break;

				case FramebufferFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_colorAttachmentsRenderID[i], GL_R32I, GL_RED_INTEGER,
						m_width, m_height, i);
					break;

				default:
					HN_CORE_ERROR("Unkonw Color Format!");
			}
		}
	}

	// Depth Attachment.
	if(m_depthAttachmentFormat != FramebufferFormat::None) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachmentRenderID);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachmentRenderID);
		switch(m_depthAttachmentFormat) {
			case FramebufferFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_depthAttachmentRenderID, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
					m_width, m_height);
				break;

			default:
				HN_CORE_ERROR("Unkonw Depth Format!");
		}
	}

	if(m_colorAttachmentsRenderID.size() > 1) {
		assert(m_colorAttachmentsRenderID.size() <= 4);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(static_cast<GLsizei>(m_colorAttachmentsRenderID.size()), buffers);
	}
	else if(m_colorAttachmentsRenderID.empty()) {
		// Only depth-pass
		glDrawBuffer(GL_NONE);
	}

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Framebuffer not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
	glViewport(0, 0, m_width, m_height);
}

void OpenGLFramebuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Resize(const uint32_t width, const uint32_t height) {
	if(width == 0 || height == 0 || width > MAX_FRAMEBUFFER_SIZE || height > MAX_FRAMEBUFFER_SIZE) {
		HN_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
		return;
	}

	m_width = width;
	m_height = height;

	Invalidate();
}

int OpenGLFramebuffer::ReadPixel(const uint32_t attachmentIndex, const int x, const int y) {
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

void OpenGLFramebuffer::ClearAttachment(const uint32_t attachmentIndex, const int value) {
	auto &format = m_colorAttachmentFormats[attachmentIndex];
	glClearTexImage(m_colorAttachmentsRenderID[attachmentIndex], 0,
		Utils::GetOpenGLTextureFormat(format), GL_INT, &value);
}

void OpenGLFramebuffer::Delete() {
	glDeleteFramebuffers(1, &m_rendererID);
	glDeleteTextures(static_cast<GLsizei>(m_colorAttachmentsRenderID.size()),
					 static_cast<GLuint *>(m_colorAttachmentsRenderID.data()));
	glDeleteTextures(1, &m_depthAttachmentRenderID);
}

} // namespace Hina
