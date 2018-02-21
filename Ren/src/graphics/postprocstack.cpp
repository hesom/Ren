#include "graphics/postprocstack.h"
#include "graphics/postprocbuffer.h"
#include "graphics/shadermanager.h"

namespace ren
{
    PostProcessingStack::PostProcessingStack()
    {
        m_vertices = {
            -1, -1,
             1, -1,
            -1,  1,
             1,  1
        };

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    auto PostProcessingStack::addEffect(const std::string& shader)->void
    {
        auto buffer = std::make_shared<PostProcessingBuffer>();
        m_passes.emplace_back(shader, buffer);
    }

    auto PostProcessingStack::getFirstBuffer() -> std::shared_ptr<PostProcessingBuffer>
    {
        return m_passes.at(0).second;
    }
    auto PostProcessingStack::setRenderTarget() -> void
    {
        m_passes.at(0).second->bind();
    }
    auto PostProcessingStack::hasPasses() const -> bool
    {
        return !m_passes.empty();
    }
    auto PostProcessingStack::doPostProcessing() const -> void
    {
        for(size_t i = 0; i < m_passes.size(); i++)
        {
            const auto pass = m_passes[i];
            const auto shader = ShaderManager::get(pass.first);
            const auto currentImage = pass.second->getColorTexture();

            if(i == m_passes.size()-1)  // last pass
            {   
                // Render to default framebuffer
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
            else
            {
                m_passes[i + 1].second->bind();
            }
            shader->bind();
            shader->setUniformValue("image", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, currentImage);
            glBindVertexArray(m_vao);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
}
