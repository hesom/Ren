#pragma once

#include "glad/glad.h"
#include <string>
namespace ren
{
    class Texture
    {
    private:
        GLuint m_textureId = 0;
        GLuint m_width = 0;
        GLuint m_height = 0;
        std::string m_type;

    public:

        auto fromFile(std::string path) -> void;

        void allocate(
            GLuint width,
            GLuint height,
            GLboolean mipmaps,
            GLenum internalFormat
        );
        auto buffer(const unsigned char* data, int channels) const -> void;
        auto bind() const -> void;
        auto bind(GLuint textureUnit) const -> void;
        static auto unbind() -> void;
        auto setType(const std::string& type) -> void;
        auto getType() const -> const decltype(m_type)&;
    };
}