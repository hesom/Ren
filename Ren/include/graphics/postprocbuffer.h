#pragma once
#include "glad/glad.h"

namespace ren
{
    class PostProcessingBuffer
    {
    private:
        GLuint m_frameBuffer{};
        GLuint m_colorTexture{};
        GLuint m_depthTexture{};

    public:
        PostProcessingBuffer();
        ~PostProcessingBuffer();
        auto bind() const ->void;
        auto unbind() const ->void;
        auto getColorTexture() const -> decltype(m_colorTexture);
    };
}