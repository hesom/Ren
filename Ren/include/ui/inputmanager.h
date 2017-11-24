#pragma once
#include <vector>
#include <memory>
#include "keylistener.h"
#include "mouselistener.h"

namespace ren
{
	class InputManager
	{
	private:
		InputManager();
		double m_mouseX_old = 0;
		double m_mouseY_old = 0;
		std::vector<IKeyListener*> keyListeners;
		std::vector<IMouseListener*> mouseListeners;
	public:
		static InputManager& getInstance();

		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		void handleKeyPressedEvent(const int key, const int mods);
		void handleKeyReleasedEvent(const int key, const int mods);
		void handleMousePressedEvent(const int button, const int mods);
		void handleMouseReleasedEvent(const int button, const int mods);
		void handleCursorEvent(const double xpos, const double ypos);
		void handleScrollEvent(const double xoffset, const double yoffset);

		void attachMouseListener (IMouseListener* mouseListener);
		void detachMouseListener(const IMouseListener* mouseListener);

		void attachKeyListener(IKeyListener* keyListener);
		void detachKeyListener(const IKeyListener* keyListener);

	private:
		static Key mapKey(int glfwKey);
		static std::vector<KeyMod> mapMods(int glfwMod);
		static MouseButton mapMouse(int glfwMouse);
	};

	
}


