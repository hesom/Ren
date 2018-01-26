#include <iostream>
#include <memory>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"
#include "graphics/fpscamera.h"
#include "graphics/entitymanager.h"
#include "graphics/waterrenderer.h"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
	using namespace ren;
	Rengine engine;
	//Listener listener;

    std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
    engine.setMainCamera(camera);
    auto well = EntityManager::loadFromFile("table_medieval_trestle.obj");
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0.0f, 0.2f, 0.0f));
    well->setTransformation(transformation);
    EntityManager::addDirectionalLight(glm::vec3(0.0f, 10000.0f, 0.0f), glm::vec3(3.0f));
    WaterRenderer::addTile(std::make_shared<WaterTile>(0.0f, 0.0f, 0.0f));
	//InputManager::detachKeyListener(&listener);
    
	engine.start();
}