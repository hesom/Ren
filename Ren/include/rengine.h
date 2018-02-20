#pragma once

#include <memory>
#include "ui/inputmanager.h"
#include "graphics/fpscamera.h"
#include "graphics/entitymanager.h"
#include "graphics/waterrenderer.h"
#include "graphics/entityrenderer.h"

namespace ren
{
    class Projection;
    class Camera;
    class Rengine
    {
    private:
        std::shared_ptr<Camera> m_mainCamera;
        std::shared_ptr<Projection> m_projection;
        static auto createWindow() -> void;
        auto loadShaders() const -> void;
    public:
        Rengine();

        auto setMainCamera(std::shared_ptr<Camera> camera) -> void;
        auto start() -> void;
    };
}


