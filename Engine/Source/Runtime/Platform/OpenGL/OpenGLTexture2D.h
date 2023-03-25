#pragma once

#include "RenderCore/Texture2D.h"

#include <glad/glad.h>

namespace Hina
{

class OpenGLTexture2D final : public Texture2D
{
public:
	OpenGLTexture2D(const std::string &path);

	OpenGLTexture2D() = default;
	OpenGLTexture2D(const OpenGLTexture2D &) = default;
	OpenGLTexture2D &operator=(const OpenGLTexture2D &) = default;
	OpenGLTexture2D(OpenGLTexture2D &&) = default;
	OpenGLTexture2D &operator=(OpenGLTexture2D &&) = default;
	virtual ~OpenGLTexture2D();

	virtual const uint32_t GetWidth() const override { return m_width; }
	virtual const uint32_t GetHeight() const override { return m_height; }
	virtual const uint32_t GetRenderID() const override { return m_renderID; }
	virtual const std::string &GetPath() const override { return m_path; }

	virtual void Bind(const uint32_t slot) const override;

	virtual inline bool operator==(const Texture &other) const override {
		return m_renderID == other.GetRenderID();
	}

private:
	std::string m_path;
	uint32_t m_width, m_height;
	uint32_t m_renderID;
	GLenum m_internalFormat, m_dataFormat;
};

} // namespace Hina
