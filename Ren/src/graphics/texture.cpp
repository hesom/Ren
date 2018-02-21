#include "graphics/texture.h"

#include "glad/glad.h"
#include "util/stb_image.h"

namespace ren
{

    auto Texture::fromFile(std::string path) -> void
    {
        int width, height, channels;
        const auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GLenum format = 0;
        if (channels == 1) {
            format = GL_R8;
        }
        else if (channels == 3) {
            format = GL_RGB8;
        }
        else
        {
            format = GL_RGBA8;
        }
        this->allocate(width, height, GL_TRUE, format);
        this->buffer(data, channels);
        stbi_image_free(data);
    }

    auto Texture::allocate(const GLuint width, const GLuint height, const GLboolean mipmaps,
                           const GLenum internalFormat) -> void
    {
        m_width = width;
        m_height = height;
        auto levels = 1;
        if (mipmaps == GL_TRUE){
            while ((width | height) >> levels) levels += 1;
        }
		
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 4.0f);
        glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, m_width, m_height);
    }

    auto Texture::buffer(const unsigned char* data, const int channels) const -> void
    {
        GLenum format;
        switch (channels) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        default:
            format = GL_RGBA;
            break;
        }

        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    auto Texture::bind() const -> void
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    auto Texture::bind(const GLuint textureUnit) const -> void
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    auto Texture::unbind() -> void
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    auto Texture::setType(const std::string& type) -> void
    {
        m_type = type;
    }
    auto Texture::getType() const -> const decltype(m_type)&
    {
        return m_type;
    }
}
