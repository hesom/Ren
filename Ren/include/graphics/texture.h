#pragma once

#include "glad/glad.h"
namespace ren
{
    class Texture
    {
    private:
        GLuint m_textureID;
        GLuint m_width;
        GLuint m_height;

    public:
        ~Texture();

        void allocate(
            GLuint width,
            GLuint height,
            GLboolean mipmaps,
            GLenum internalFormat
        );
        void buffer(const unsigned char* data);
        void bind();
        void bind(GLuint textureUnit);
        void unbind();
    };
}