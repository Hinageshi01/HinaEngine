#pragma once

#include "RenderCore/Framebuffer.h"

namespace Hina
{

class OpenGLFramebuffer final : public Framebuffer
{
public:
	OpenGLFramebuffer(const FramebufferInitializer &init);

	OpenGLFramebuffer() = default;
	OpenGLFramebuffer(const OpenGLFramebuffer &) = default;
	OpenGLFramebuffer &operator=(const OpenGLFramebuffer &) = default;
	OpenGLFramebuffer(OpenGLFramebuffer &&) = default;
	OpenGLFramebuffer &operator=(OpenGLFramebuffer &&) = default;
	virtual ~OpenGLFramebuffer();

	void Invalidate();

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual uint32_t GetWidth() override { return m_width; }
	virtual uint32_t GetHeight() override { return m_height; }

	virtual void Resize(const uint32_t width, const uint32_t height) override;
	virtual int ReadPixel(const uint32_t attachmentIndex, const int x, const int y) override;

	virtual void ClearAttachment(const uint32_t attachmentIndex, const int value) override;

	virtual uint32_t GetColorAttachmentRenderID(const uint32_t index = 0) const override {
		assert(index < m_colorAttachmentsRenderID.size());
		return m_colorAttachmentsRenderID[index];
	}

private:
	void Delete();

	uint32_t m_rendererID = 0;
	uint32_t m_depthAttachmentRenderID = 0;
	std::vector<uint32_t> m_colorAttachmentsRenderID;

	std::vector<FramebufferFormat> m_colorAttachmentFormats;
	FramebufferFormat m_depthAttachmentFormat = FramebufferFormat::None;

	uint32_t m_width;
	uint32_t m_height;
};

} // namespace Hina
