#pragma once

namespace Hina
{

enum class FramebufferFormat
{
	None = 0,

	// Color
	RGBA8,
	RED_INTEGER,

	// Depth/stencil
	DEPTH24STENCIL8,
};

struct FramebufferInitializer
{
	FramebufferInitializer() = default;
	FramebufferInitializer(const FramebufferInitializer &) = default;
	FramebufferInitializer &operator=(const FramebufferInitializer &) = default;
	FramebufferInitializer(FramebufferInitializer &&) = default;
	FramebufferInitializer &operator=(FramebufferInitializer &&) = default;
	~FramebufferInitializer() = default;

	uint32_t m_width = 1600, m_height = 900;
	std::vector<FramebufferFormat> m_attachmentFormats = { FramebufferFormat::RGBA8, FramebufferFormat::DEPTH24STENCIL8 };

	bool m_swapChainTarget = false;
};

class Framebuffer
{
public:
	static std::shared_ptr<Framebuffer> Create(const FramebufferInitializer &init = FramebufferInitializer());

public:
	Framebuffer() = default;
	Framebuffer(const Framebuffer &) = default;
	Framebuffer &operator=(const Framebuffer &) = default;
	Framebuffer(Framebuffer &&) = default;
	Framebuffer &operator=(Framebuffer &&) = default;
	virtual ~Framebuffer() = default;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual uint32_t GetWidth() = 0;
	virtual uint32_t GetHeight() = 0;

	virtual void Resize(const uint32_t width, const uint32_t height) = 0;
	virtual int ReadPixel(const uint32_t attachmentIndex, const int x, const int y) = 0;

	virtual void ClearAttachment(const uint32_t attachmentIndex, const int value) = 0;

	virtual uint32_t GetColorAttachmentRenderID(const uint32_t index = 0) const = 0;
};

} // namespace Hina
