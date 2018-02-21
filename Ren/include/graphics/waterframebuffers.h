#pragma once

#include <glad/glad.h>

namespace ren
{
    class WaterFramebuffers
    {
    private:
        GLuint m_reflectionFramebuffer{};
        GLuint m_reflectionTexture{};
        GLuint m_reflectionDepthBuffer{};

        GLuint m_refractionFramebuffer{};
        GLuint m_refractionTexture{};
        GLuint m_refractionDepthTexture{};

        auto initializeReflectionFramebuffer() -> void;
        auto initializeRefractionFramebuffer() -> void;
        auto bindFramebuffer(GLuint frameBuffer, int width, int height) const -> void;
        auto createFramebuffer() const -> GLuint;
        auto createTextureAttachment(int width, int height) const -> GLuint;
        auto createDepthTextureAttachment(int width, int height) const -> GLuint;
        auto createDepthBufferAttachment(int width, int height) const -> GLuint;

    public:
        static int reflection_width;
        static int reflection_height;
        static int refraction_width;
        static int refraction_height;

        WaterFramebuffers();

        auto cleanUp() const -> void;
        auto bindReflectionFramebuffer() const -> void;
        auto bindRefractionFramebuffer() const -> void;
        auto unbindCurrentFramebuffer() const -> void;
        auto getReflectionTexture() const -> decltype(m_reflectionTexture);
        auto getRefractionTexture() const -> decltype(m_refractionTexture);
        auto getRefractionDepthTexture() const -> decltype(m_refractionDepthTexture);
    };
}