#pragma once
#include <vector>
namespace ren
{
	class IMouseListener
	{
	public:
		virtual void onMousePressed(MouseButton button, std::vector<KeyMod> mods) = 0;
		virtual void onMouseReleased(MouseButton button, std::vector<KeyMod> mods) = 0;
		virtual void onMouseMoved(double xpos, double ypos, double dx, double dy) = 0;
		virtual void onMouseScroll(double xoffset, double yoffset) = 0;
	};
}

