#include "inputmanager.h"
#include "../debugging/debug.h"
#include "GLFW/glfw3.h"

#include <algorithm>

namespace ren
{
	InputManager::InputManager()
	{
	}

	InputManager& InputManager::getInstance()
	{
		static InputManager instance;
		return instance;
	}

	void InputManager::handleKeyPressedEvent(const int key, const int mods)
	{
		for (auto& listener : keyListeners) {
			listener->onKeyPressed(mapKey(key), mapMods(mods));
		}

	}

	void InputManager::handleKeyReleasedEvent(const int key, const int mods)
	{
		for (auto& listener : keyListeners) {
			listener->onKeyReleased(mapKey(key), mapMods(mods));
		}
	}

	void InputManager::handleMousePressedEvent(const int button, const int mods)
	{
		for (auto& listener : mouseListeners) {
			listener->onMousePressed(mapMouse(button), mapMods(mods));
		}
	}

	void InputManager::handleMouseReleasedEvent(const int button, const int mods)
	{
		for (auto& listener : mouseListeners) {
			listener->onMouseReleased(mapMouse(button), mapMods(mods));
		}
	}

	void InputManager::handleCursorEvent(const double xpos, const double ypos)
	{
		double dx = m_mouseX_old - xpos;
		double dy = m_mouseY_old - ypos;
		m_mouseX_old = xpos;
		m_mouseY_old = ypos;
		for (auto& listener : mouseListeners) {
			listener->onMouseMoved(xpos, ypos, dx, dy);
		}
	}

	void InputManager::handleScrollEvent(const double xoffset, const double yoffset)
	{
		for (auto& listener : mouseListeners) {
			listener->onMouseScroll(xoffset, yoffset);
		}
	}

	void InputManager::attachMouseListener(IMouseListener* mouseListener)
	{
		mouseListeners.push_back(mouseListener);
	}

	void InputManager::detachMouseListener(const IMouseListener* mouseListener)
	{
		std::remove(mouseListeners.begin(), mouseListeners.end(), mouseListener);
	}

	void InputManager::attachKeyListener(IKeyListener* keyListener)
	{
		keyListeners.push_back(keyListener);
	}

	void InputManager::detachKeyListener(const IKeyListener* keyListener)
	{
		std::remove(keyListeners.begin(), keyListeners.end(), keyListener);
	}
}

