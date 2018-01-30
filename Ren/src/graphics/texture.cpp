#include "graphics/texture.h"

#include "glad/glad.h"
#include "util/stb_image.h"

namespace ren
{

    auto Texture::fromFile(std::string path) -> void
    {
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GLenum format;
        if (channels == 1) {
            format = GL_R8;
        }
        else if (channels == 3) {
            format = GL_RGB8;
        }
        else if (channels == 4) {
            format = GL_RGBA8;
        }
        this->allocate(width, height, GL_TRUE, format);
        this->buffer(data, channels);
        stbi_image_free(data);
    }

    auto Texture::allocate(GLuint width, GLuint height, GLboolean mipmaps, GLenum internalFormat) -> void
    {
        m_width = width;
        m_height = height;
        int levels = 1;
        if (mipmaps == GL_TRUE){
            while ((width | height) >> levels) levels += 1;
        }
		
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 4.0f);
        glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, m_width, m_height);
    }

    auto Texture::buffer(const unsigned char* data, int channels) -> void
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

        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    auto Texture::bind() -> void
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    auto Texture::bind(GLuint textureUnit) -> void
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    auto Texture::unbind() -> void
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    auto Texture::setType(std::string type) -> void
    {
        m_type = type;
    }
    auto Texture::getType() const -> const decltype(m_type)&
    {
        return m_type;
    }
}