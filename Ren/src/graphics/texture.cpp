#include "graphics/texture.h"

#include "glad/glad.h"
namespace ren
{
    Texture::~Texture()
    {
        glDeleteTextures(1, &m_textureID);
    }

    void Texture::allocate(GLuint width, GLuint height, GLboolean mipmaps, GLenum internalFormat)
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, m_width, m_height);
    }

    void Texture::buffer(const unsigned char * data)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture::bind(GLuint textureUnit)
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}