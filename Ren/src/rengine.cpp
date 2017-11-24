#include <iostream>
#include <GLFW/glfw3.h>

#include "rengine.h"
#include "ui/windowmanager.h"


namespace ren
{
	Rengine::Rengine()
	{
		createWindow();
	}

	void Rengine::start()
	{
		while (!WindowManager::exitRequested()) {
			WindowManager::updateWindow();
		}

		WindowManager::destroyWindow();
	}

	void Rengine::createWindow()
	{
		WindowManager::init();
		WindowManager::createWindow(800, 600, "My Window");
	}
}
