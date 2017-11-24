#include "Listener.h"
#include "ui/inputmanager.h"
#include <iostream>

Listener::Listener()
{
	InputManager::getInstance().attachKeyListener(this);
	InputManager::getInstance().attachMouseListener(this);
}

void Listener::onKeyPressed(Key key, std::vector<KeyMod> mods)
{
	std::cout << (int)key << std::endl;
}

void Listener::onKeyReleased(Key key, std::vector<KeyMod> mods)
{
}

void Listener::onMousePressed(MouseButton button, std::vector<KeyMod> mods)
{
}

void Listener::onMouseReleased(MouseButton button, std::vector<KeyMod> mods)
{
}

void Listener::onMouseMoved(double xpos, double ypos, double dx, double dy)
{
	std::cout << "dx:" << dx << std::endl;
	std::cout << "dy:" << dy << std::endl;
	std::cout << std::endl;
}

void Listener::onMouseScroll(double xoffset, double yoffset)
{
}
