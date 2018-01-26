#pragma once
#include <vector>
#include <memory>

#include "graphics/watertile.h"
#include "glad/glad.h"
#include "graphics/camera.h"

namespace ren
{
    class WaterRenderer
    {
    private:
        static std::vector<std::shared_ptr<WaterTile>> m_tiles;
        static GLuint m_vao;
        static GLuint m_vbo;

        static auto setUp() -> void;
    public:
        static auto render(std::shared_ptr<Camera> camera) -> void;
        static auto addTile(std::shared_ptr<WaterTile> tile) -> void;
    };
}