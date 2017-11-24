#include <iostream>
#include <rengine.h>

#include "Listener.h"
#include "ui/inputmanager.h"
int main()
{
	using namespace ren;
	Rengine engine;
	Listener listener;
	InputManager::getInstance().detachKeyListener(&listener);
	engine.start();
}