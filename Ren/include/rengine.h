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
        void createWindow();
    public:
        Rengine();

        void setMainCamera(std::shared_ptr<Camera> camera);
        void start();
    };
}


