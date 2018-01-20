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
    auto well = EntityManager::loadFromOBJ("well.obj");
	//InputManager::detachKeyListener(&listener);
    
	engine.start();
}