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

	uint32_t m_width = 0, m_height = 0;
	std::vector<FramebufferFormat> m_attachmentFormats;

	bool m_swapChainTarget = false;
};

class Framebuffer
{
public:
	Framebuffer() = default;
	Framebuffer(const Framebuffer &) = default;
	Framebuffer &operator=(const Framebuffer &) = default;
	Framebuffer(Framebuffer &&) = default;
	Framebuffer &operator=(Framebuffer &&) = default;
	virtual ~Framebuffer() = default;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual void Resize(uint32_t width, uint32_t height) = 0;
	virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

	virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

	virtual uint32_t GetColorAttachmentRenderID(uint32_t index = 0) const = 0;

	static std::unique_ptr<Framebuffer> Create(const FramebufferInitializer &init);
};

} // namespace Hina
