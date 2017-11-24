#pragma once
#include "keymap.h"

namespace ren
{
	class IKeyListener
	{
	public:
		virtual void onKeyPressed(Key key, std::vector<KeyMod> mods) = 0;
		virtual void onKeyReleased(Key key, std::vector<KeyMod> mods) = 0;
	};
}

