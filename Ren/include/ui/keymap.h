#pragma once
namespace ren
{
	enum class Key
	{
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_BACKSPACE,
		KEY_RETURN,
		KEY_SPACE,
		KEY_CAPSLOCK,
		KEY_SHIFT,
		KEY_CTRL,
		KEY_ALT,
		KEY_TAB,
		KEY_ESC,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_PRINT,
		KEY_SCROLL,
		KEY_PAUSE,
		KEY_INSERT,
		KEY_REMOVE,
		KEY_POS1,
		KEY_END,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		ERROR
	};

	enum class MouseButton
	{
		MOUSE_1,
		MOUSE_2,
		MOUSE_3,
		MOUSE_4,
		MOUSE_5,
		MOUSE_6,
		MOUSE_7,
		MOUSE_8,
		ERROR
	};

	enum class KeyMod
	{
		MOD_SHIFT = 0x0001,
		MOD_CTRL = 0x0002,
		MOD_ALT = 0x0004,
		MOD_WIN = 0x0008,
		ERROR = 0x1111,
	};

	
}

