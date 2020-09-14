#include <iostream>
#include "core/Window.h"

extern Window* WindowInstance();

int main(void)
{
	Window* tempWindow = WindowInstance();
	tempWindow->Run();
	delete tempWindow;
	return 0;
}