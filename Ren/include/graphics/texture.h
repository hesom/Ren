#pragma once

#include "glad/glad.h"
#include <string>
namespace ren
{
    class Texture
    {
    private:
        GLuint m_textureID;
        GLuint m_width;
        GLuint m_height;
        std::string m_type;

    public:

        auto fromFile(std::string path) -> void;

        void allocate(
            GLuint width,
            GLuint height,
            GLboolean mipmaps,
            GLenum internalFormat
        );
        auto buffer(const unsigned char* data, int channels) -> void;
        auto bind() -> void;
        auto bind(GLuint textureUnit) -> void;
        auto unbind() -> void;
        auto setType(std::string type) -> void;
        auto getType() const -> const decltype(m_type)&;
    };
}