#include "hnpch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

#include <stb_image.h>

namespace Hina
{

OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height)
	: m_width(width), m_height(height) {

	m_internalFormat = GL_RGBA8;
	m_dataFormat = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
	glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

	// TODO : Expose thses options.
	glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_path(path) {
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc *data = nullptr;
	data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	HN_CORE_ASSERT(data, "Faild to load texture at {}.", m_path);

	m_width = width;
	m_height = height;
	m_isLoaded = true;

	GLenum internalFormat = 0, dataFormat = 0;
	if(channels == 4) {
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if(channels == 3) {
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	m_internalFormat = internalFormat;
	m_dataFormat = dataFormat;

	HN_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
	glTextureStorage2D(m_rendererID, 1, internalFormat, m_width, m_height);

	glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
	glDeleteTextures(1, &m_rendererID);
}

void OpenGLTexture2D::SetData(void *data, const uint32_t size) {
	uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
	HN_CORE_ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
	glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(uint32_t slot) const {
	glBindTextureUnit(slot, m_rendererID);
}

} // namespace Hina
