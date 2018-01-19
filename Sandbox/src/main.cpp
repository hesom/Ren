#include <iostream>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"
#include "graphics/fpscamera.h"

int main()
{
	using namespace ren;
	Rengine engine;
	//Listener listener;

    FPSCamera camera;

	//InputManager::detachKeyListener(&listener);
    
	engine.start();
}