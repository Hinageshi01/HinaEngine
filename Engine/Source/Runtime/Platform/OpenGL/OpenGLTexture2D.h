#pragma once

#include "Renderer/Texture2D.h"

#include <glad/glad.h>

namespace Hina
{

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const uint32_t width, const uint32_t height);
	OpenGLTexture2D(const std::string &path);
	virtual ~OpenGLTexture2D();

	virtual const uint32_t GetWidth() const override { return m_width; }
	virtual const uint32_t GetHeight() const override { return m_height; }
	virtual const uint32_t GetRendererID() const override { return m_rendererID; }
	virtual const std::string &GetPath() const override { return m_path; }

	virtual void SetData(void *data, const uint32_t size) override;

	virtual void Bind(const uint32_t slot) const override;

	virtual bool IsLoaded() const override { return m_isLoaded; }

	virtual inline bool operator==(const Texture &other) const override {
		return m_rendererID == other.GetRendererID();
	}

private:
	std::string m_path;
	bool m_isLoaded = false;
	uint32_t m_width, m_height;
	uint32_t m_rendererID;
	GLenum m_internalFormat, m_dataFormat;
};

} // namespace Hina
