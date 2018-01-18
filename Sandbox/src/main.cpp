#include <iostream>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"

int main()
{
	using namespace ren;
	Rengine engine;
	Listener listener;

	InputManager::detachKeyListener(&listener);
    
	engine.start();
}