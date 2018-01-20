#pragma once
#include "keymap.h"
#include <vector>
namespace ren
{
	/*! Implement this interface to be able to subscribe to mouse events.
		Each of these functions will only be called when the corresponding mouse
		event occured. Make sure to call InputerManager::attachMouseListener to attach your
		listener
	*/
	class IMouseListener
	{
	public:
		virtual auto onMousePressed(MouseButton button, std::vector<KeyMod> mods) -> void = 0;
		virtual auto onMouseReleased(MouseButton button, std::vector<KeyMod> mods) -> void = 0;
		virtual auto onMouseMoved(double xpos, double ypos, double dx, double dy) -> void = 0;
		virtual auto onMouseScroll(double xoffset, double yoffset) -> void = 0;
	};
}

