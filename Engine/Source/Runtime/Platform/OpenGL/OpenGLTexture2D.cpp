#include "hnpch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

#include <stb_image.h>

namespace Hina
{

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_path(path) {
	HN_PROFILE_FUNCTION();

	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;
	stbi_uc *data = nullptr;

	{
		HN_PROFILE_SCOPE("stbi_uc *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp)");
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	}

	if(data) {
		m_width = width;
		m_height = height;

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

		HN_CORE_ASSERT(m_internalFormat & m_dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderID);

		glTextureStorage2D(m_renderID, 1, m_internalFormat, m_width, m_height);

		glTextureParameteri(m_renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_renderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_renderID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_renderID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		{
			HN_PROFILE_SCOPE("void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)");
			glTextureSubImage2D(m_renderID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
		}

		glGenerateTextureMipmap(m_renderID);

		stbi_image_free(data);
	}
	else {
		HN_CORE_ERROR("Faild to load texture at {}.", m_path);
	}
}

OpenGLTexture2D::~OpenGLTexture2D() {
	glDeleteTextures(1, &m_renderID);
}

void OpenGLTexture2D::Bind(uint32_t slot) const {
	glBindTextureUnit(slot, m_renderID);
}

} // namespace Hina
