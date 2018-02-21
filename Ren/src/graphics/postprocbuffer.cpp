#include "graphics/postprocbuffer.h"
#include "ui/windowmanager.h"

namespace ren
{
    PostProcessingBuffer::PostProcessingBuffer()
    {
        const auto width = WindowManager::getWidth();
        const auto height = WindowManager::getHeight();
        glGenFramebuffers(1, &m_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);

        glGenTextures(1, &m_colorTexture);
        glBindTexture(GL_TEXTURE_2D, m_colorTexture);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colorTexture, 0);

        glGenTextures(1, &m_depthTexture);
        glBindTexture(GL_TEXTURE_2D, m_depthTexture);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, width, height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    PostProcessingBuffer::~PostProcessingBuffer()
    {
        glDeleteTextures(1, &m_depthTexture);
        glDeleteTextures(1, &m_colorTexture);
        glDeleteFramebuffers(1, &m_frameBuffer);
    }

    auto PostProcessingBuffer::bind() const -> void
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    auto PostProcessingBuffer::unbind() const -> void
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    auto PostProcessingBuffer::getColorTexture() const -> decltype(m_colorTexture)
    {
        return m_colorTexture;
    }

}

