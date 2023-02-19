#include "hnpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Hina
{

namespace
{
constexpr uint16_t s_MaxFramebufferSize = 8192;
}

namespace Utils
{

static inline GLenum TextureTarget(bool multisampled) {
	return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static inline void CreateTextures(bool multisampled, uint32_t count, uint32_t *outID) {
	glCreateTextures(TextureTarget(multisampled), count, outID);
}

static inline void BindTexture(bool multisampled, uint32_t id) {
	glBindTexture(TextureTarget(multisampled), id);
}

static inline void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index) {
	HN_PROFILE_FUNCTION();

	bool multisampled = samples > 1;
	if(multisampled) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
}

static inline void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
	HN_PROFILE_FUNCTION();

	bool multisampled = samples > 1;
	if(multisampled) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
	}
	else {
		glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
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

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferInitializer &init) : m_initializer(init) {
	for(const auto &format : m_initializer.m_attachmentFormats) {
		if(!Utils::IsDepthFormat(format)) {
			m_colorAttachmentFormats.emplace_back(format);
		}
		else {
			m_depthAttachmentFormat = format;
		}
	}

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

	bool multisample = m_initializer.m_samples > 1;

	// Attachments
	if(!m_colorAttachmentFormats.empty()) {
		m_colorAttachmentsRenderID.resize(m_colorAttachmentFormats.size());
		Utils::CreateTextures(multisample, m_colorAttachmentsRenderID.size(), m_colorAttachmentsRenderID.data());

		for(size_t i = 0; i < m_colorAttachmentsRenderID.size(); ++i) {
			Utils::BindTexture(multisample, m_colorAttachmentsRenderID[i]);
			switch(m_colorAttachmentFormats[i]) {
				case FramebufferFormat::RGBA8:
					Utils::AttachColorTexture(m_colorAttachmentsRenderID[i], m_initializer.m_samples, GL_RGBA8, GL_RGBA,
						m_initializer.m_width, m_initializer.m_height, i);
					break;

				case FramebufferFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_colorAttachmentsRenderID[i], m_initializer.m_samples, GL_R32I, GL_RED_INTEGER,
						m_initializer.m_width, m_initializer.m_height, i);
					break;

				default:
					HN_CORE_ERROR("Unkonw Color Format!");
			}
		}
	}

	if(m_depthAttachmentFormat != FramebufferFormat::None) {
		Utils::CreateTextures(multisample, 1, &m_depthAttachmentRenderID);
		Utils::BindTexture(multisample, m_depthAttachmentRenderID);
		switch(m_depthAttachmentFormat) {
			case FramebufferFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_depthAttachmentRenderID, m_initializer.m_samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
					m_initializer.m_width, m_initializer.m_height);
				break;

			default:
				HN_CORE_ERROR("Unkonw Depth Format!");
		}
	}

	if(m_colorAttachmentsRenderID.size() > 1) {
		// tmp
		assert(m_colorAttachmentsRenderID.size() <= 4);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_colorAttachmentsRenderID.size(), buffers);
	}
	else if(m_colorAttachmentsRenderID.empty()) {
		// Only depth-pass
		glDrawBuffer(GL_NONE);
	}

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
		"Framebuffer not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
	glViewport(0, 0, m_initializer.m_width, m_initializer.m_height);
}

void OpenGLFramebuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height) {
	if(width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) {
		HN_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
		return;
	}

	m_initializer.m_width = width;
	m_initializer.m_height = height;

	Invalidate();
}

int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y) {
	assert(attachmentIndex < m_colorAttachmentsRenderID.size());

	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;

}

void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
	assert(attachmentIndex < m_colorAttachmentsRenderID.size());

	auto &format = m_colorAttachmentFormats[attachmentIndex];
	glClearTexImage(m_colorAttachmentsRenderID[attachmentIndex], 0,
		Utils::GetOpenGLTextureFormat(format), GL_INT, &value);
}

void OpenGLFramebuffer::Delete() {
	glDeleteFramebuffers(1, &m_rendererID);
	glDeleteTextures(m_colorAttachmentsRenderID.size(), m_colorAttachmentsRenderID.data());
	glDeleteTextures(1, &m_depthAttachmentRenderID);
}

} // namespace Hina
