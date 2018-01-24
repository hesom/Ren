#pragma once
#include <memory>
#include "graphics/camera.h"

namespace ren
{
    class EntityRenderer
    {
    private:

    public:
        static auto render(std::shared_ptr<Camera> camera) -> void;
    };
}