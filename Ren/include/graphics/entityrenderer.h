#pragma once
#include <memory>
#include <string>
#include "graphics/camera.h"
#include "graphics/shaderprogram.h"

namespace ren
{
    class EntityRenderer
    {
    private:
        static std::string m_defaultShader;
    public:
        static auto setDefaultShader(const std::string& shader) -> void;
        static auto getDefaultShader() -> decltype(m_defaultShader);
        static auto render(const std::shared_ptr<Camera>& camera) -> void;
    };
}