#include <iostream>
#include <memory>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"
#include "graphics/fpscamera.h"

int main()
{
	using namespace ren;
	Rengine engine;
	//Listener listener;

    std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
    engine.setMainCamera(camera);
	//InputManager::detachKeyListener(&listener);
    
	engine.start();
}