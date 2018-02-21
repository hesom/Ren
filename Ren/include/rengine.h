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
    class PostProcessingStack;
    class Rengine
    {
    private:
        std::shared_ptr<Camera> m_mainCamera;
        std::shared_ptr<Projection> m_projection;
        std::shared_ptr<PostProcessingStack> m_postProcStack;
        static auto createWindow() -> void;
        auto loadShaders() const -> void;
    public:
        Rengine();

        auto setMainCamera(const std::shared_ptr<Camera>& camera) -> void;
        auto addPostProcessingEffect(const std::string& shader) const -> void;
        auto start() const -> void;
    };
}


