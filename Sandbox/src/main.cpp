#include <iostream>
#include <memory>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"
#include "graphics/fpscamera.h"
#include "graphics/entitymanager.h"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
	using namespace ren;
	Rengine engine;
	//Listener listener;

    std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
    engine.setMainCamera(camera);
    int well = EntityManager::loadFromOBJ("well.obj");
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::translate(transform, glm::vec3(5.0f, 1.0f, 1.0f));
    EntityManager::get(well)->setTransformation(transform);
	//InputManager::detachKeyListener(&listener);
    
	engine.start();
}