#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>

namespace ren
{
    class PostProcessingBuffer;
    class PostProcessingStack
    {
    private:
        std::vector<std::pair<std::string, std::shared_ptr<PostProcessingBuffer>>> m_passes{};
        std::vector<GLfloat> m_vertices;
        GLuint m_vbo{};
        GLuint m_vao{};
    public:
        PostProcessingStack();
        auto addEffect(const std::string& shader) -> void;
        auto getFirstBuffer() -> std::shared_ptr<PostProcessingBuffer>;
        auto setRenderTarget() -> void;
        auto hasPasses() const -> bool;
        auto doPostProcessing() const -> void;
    };
}
