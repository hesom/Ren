#pragma once
#include <vector>
#include <memory>
#include "ui/keylistener.h"
#include "ui/mouselistener.h"

namespace ren
{
	/*! The InputManager is a singleton class which dispatches the keyboard and mouse inputs gathered
		by the window to subscribed listener classes (aka observer design pattern)
	*/
	class InputManager
	{
	private:
		InputManager();
		static double m_mouseX_old;
		static double m_mouseY_old;
		static std::vector<IKeyListener*> m_keyListeners;
		static std::vector<IMouseListener*> m_mouseListeners;
	public:
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		/*! Handles the single event after a key is pressed down.
			\param key the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		static auto handleKeyPressedEvent(const int key, const int mods) -> void;

		/*! Handles the single event after a key is released.
			\param key the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		static auto handleKeyReleasedEvent(const int key, const int mods) -> void;

		/*! Handles the single event after a key is pressed.
			\param button the glfw mouse button id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		static auto handleMousePressedEvent(const int button, const int mods) -> void;

		/*! Handles the single event after a key is released.
			\param button the glfw key id
			\param mods the glfw mod keys pressed, encoded in a single int (shift, alt, etc)
		*/
		static auto handleMouseReleasedEvent(const int button, const int mods) -> void;

		/*! Handles the event after the mouse is released.
			\param xpos the x position of the mouse. 0 is top left of the window
			\param ypos the y position of the mouse. 0 is top left of the window
		*/
		static auto handleCursorEvent(const double xpos, const double ypos) -> void;

		/*! Handles the event after scrolling with the mouse wheel 
			\param xoffset how far the mouse wheel was scrolled from left to right 
			\param yoffset how far the mouse wheel was scrolled from top to bottom
		*/
		static auto handleScrollEvent(const double xoffset, const double yoffset) -> void;

		/*! Attaches a IMouseListener that gets notified each time a mouse event occurs
			\param mouseListener pointer to the IMouseListener to be attached
		*/
		static auto attachMouseListener (IMouseListener* mouseListener) -> void;

		/*! Detaches a IMouseListener to unsubscribed from event notifications
			\param mouseListener pointer to the IMouseListener to be detached
		*/
		static auto detachMouseListener(const IMouseListener* mouseListener) -> void;

		/*! Attaches a IKeyListener that gets notified each time a keyboard event occurs
			\param keyListener pointer to the IKeyListener to be attached
		*/
		static auto attachKeyListener(IKeyListener* keyListener) -> void;

		/*! Detaches a IKeyListener to unsubscribed from event notifications
			\param keyListener pointer to the IKeyListener to be detached
		*/
		static auto detachKeyListener(const IKeyListener* keyListener) -> void;

	private:
		/*! Maps glfw key enum values to a safer internal enum class format */
		static auto mapKey(int glfwKey) -> Key;
		/*! Maps glfw mod enum values to a safer internal enum class format */
		static auto mapMods(int glfwKey) -> std::vector<KeyMod>;
		/*! Maps glfw mouse button enum values to a safer internal enum class format */
		static auto mapMouse(int glfwMouse) -> MouseButton;
	};

	
}


