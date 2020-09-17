#ifndef KEYBOARD_HEADER
#define KEYBOARD_HEADER

#include "KeyCode.h"
#include "Windows.h"

class Keyboard
{
public:
	~Keyboard();

	inline static bool IsKeyDown(KeyCode aKeyCode) { return GetKeyState((int)aKeyCode) & 0x8000 ? true : false; }

private:
	Keyboard();
};
#endif