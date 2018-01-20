#pragma once

#include <memory>
#include "graphics/camera.h"
#include "graphics/projection.h"

namespace ren
{
    class Rengine
    {
    private:
        std::shared_ptr<Camera> m_mainCamera;
        Projection m_projection;
        auto createWindow() -> void;
    public:
        Rengine();

        auto setMainCamera(std::shared_ptr<Camera> camera) -> void;
        auto start() -> void;
    };
}


