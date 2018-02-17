#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "glad/glad.h"

#include "rengine.h"
#include "ui/windowmanager.h"
#include "graphics/mesh.h"
#include "glm/glm.hpp"
#include "graphics/shaderprogram.h"
#include "graphics/shadermanager.h"
#include "graphics/entitymanager.h"
#include "graphics/entityrenderer.h"
#include "graphics/waterrenderer.h"
#include "graphics/waterframebuffers.h"
#include "util/timer.h"
#include "graphics/camera.h"
#include "graphics/projection.h"

namespace ren
{
    Rengine::Rengine()
    {
        createWindow();
        m_projection = std::make_shared<Projection>(90.0f, 0.1f, 100.0f, 1280, 720);
    }

    auto Rengine::setMainCamera(std::shared_ptr<Camera> camera) -> void
    {
        m_mainCamera = camera;
    }

    auto Rengine::start() -> void
    {
        loadShaders();
        glm::mat4 projectionMatrix = m_projection->getProjectionMatrix();
        auto waterFBOs = std::make_shared<WaterFramebuffers>();

        while (!WindowManager::exitRequested()) {
            Timer::tick();
            m_mainCamera->update();

            auto entityDefaultShader = ShaderManager::get(EntityRenderer::getDefaultShader());

            entityDefaultShader->setUniformMatrix("projectionMatrix", projectionMatrix);
            ShaderManager::get("WaterShader")->setUniformMatrix("projectionMatrix", projectionMatrix);

            if (WaterRenderer::getTiles().size() != 0) {
                auto waterTile = WaterRenderer::getTiles().at(0);
                float cameraDistance = 2 * (m_mainCamera->getPosition().y - waterTile->getHeight());
                auto waterCamera = std::make_shared<Camera>(*m_mainCamera);
                waterCamera->setPosition(glm::vec3(
                    waterCamera->getPosition().x,
                    waterCamera->getPosition().y - cameraDistance,
                    waterCamera->getPosition().z));
                waterCamera->invertPitch();

                //Water reflection pass
                entityDefaultShader->setUniformValue("plane", glm::vec4(0.0f, 1.0f, 0.0f, -waterTile->getHeight()));
                waterFBOs->bindReflectionFramebuffer();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                EntityRenderer::render(waterCamera);
                waterFBOs->unbindCurrentFramebuffer();
                //Water refraction pass
                entityDefaultShader->setUniformValue("plane", glm::vec4(0.0f, -1.0f, 0.0f, waterTile->getHeight()));
                waterFBOs->bindRefractionFramebuffer();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                EntityRenderer::render(m_mainCamera);
                waterFBOs->unbindCurrentFramebuffer();
            }

            //Main pass
            entityDefaultShader->setUniformValue("plane", glm::vec4(0.0f, -1.0f, 0.0f, 100000.0f));
            EntityRenderer::render(m_mainCamera);

            WaterRenderer::render(m_mainCamera, waterFBOs);

            WindowManager::updateWindow();
        }

        waterFBOs->cleanUp();
        WindowManager::destroyWindow();
    }

    auto Rengine::createWindow() -> void
    {
        WindowManager::init();
        WindowManager::createWindow(1280, 720, "My Window");
    }
    auto Rengine::loadShaders() -> void
    {
        std::string vertexSource =
#include "graphics/shaders/entityshader.vert"
            ;
        std::string fragmentSource =
#include "graphics/shaders/entityshader.frag"
            ;

        ShaderManager::add(vertexSource, fragmentSource, "EntityShader");

        vertexSource =
#include "graphics/shaders/watershader.vert"
            ;
        fragmentSource =
#include "graphics/shaders/watershader.frag"
            ;

        ShaderManager::add(vertexSource, fragmentSource, "WaterShader");

        vertexSource =
#include "graphics/shaders/toonshader.vert"
            ;
        fragmentSource =
#include "graphics/shaders/toonshader.frag"
            ;

        ShaderManager::add(vertexSource, fragmentSource, "ToonShader");
    }
}
