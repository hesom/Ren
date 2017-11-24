#pragma once
#include "keymap.h"
#include <vector>
namespace ren
{
	class IKeyListener
	{
	public:
		virtual void onKeyPressed(Key key, std::vector<KeyMod> mods) = 0;
		virtual void onKeyReleased(Key key, std::vector<KeyMod> mods) = 0;
	};
}

