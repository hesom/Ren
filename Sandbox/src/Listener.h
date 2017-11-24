#pragma once
#include <ui/keylistener.h>
#include <ui/mouselistener.h>

using namespace ren;
class Listener : public IKeyListener, public IMouseListener
{
public:
	Listener();
	void onKeyPressed(Key key, std::vector<KeyMod> mods) override;
	void onKeyReleased(Key key, std::vector<KeyMod> mods) override;
	void onMousePressed(MouseButton button, std::vector<KeyMod> mods) override;
	void onMouseReleased(MouseButton button, std::vector<KeyMod> mods) override;
	void onMouseMoved(double xpos, double ypos, double dx, double dy) override;
	void onMouseScroll(double xoffset, double yoffset) override;
};