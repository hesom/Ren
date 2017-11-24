#include <iostream>
#include <GLFW/glfw3.h>

#include "ren.h"
#include "ui/windowmanager.h"

int createWindow()
{
	using namespace ren;

	WindowManager::init();
	WindowManager::createWindow(800, 600, "My Window");
	while (!WindowManager::exitRequested()) {
		WindowManager::updateWindow();
	}

	WindowManager::destroyWindow();
	return 0;
}