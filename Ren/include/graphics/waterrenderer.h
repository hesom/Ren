#pragma once
#include <vector>
#include <memory>

#include "graphics/watertile.h"
#include "glad/glad.h"
#include "graphics/camera.h"
#include "graphics/waterframebuffers.h"
#include "graphics/texture.h"

namespace ren
{
    class WaterRenderer
    {
    private:
        static std::vector<std::shared_ptr<WaterTile>> m_tiles;
        static GLuint m_vao;
        static GLuint m_vbo;
        static std::shared_ptr<Texture> dudvMap;
        static std::shared_ptr<Texture> normalMap;
        static float m_wave_speed;
        static float m_animation_timer;

        static auto setUp() -> void;
    public:
        static auto render(std::shared_ptr<Camera> camera, std::shared_ptr<WaterFramebuffers> fbos) -> void;
        static auto addTile(std::shared_ptr<WaterTile> tile) -> void;
        static auto getTiles() -> const decltype(m_tiles)&;
    };
}