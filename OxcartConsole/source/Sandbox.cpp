#include "core/Window.h"

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize)
		: Window::Window(aTitle, aScreenWidth, aScreenHeight, aPixelSize)
	{

	}

	void OnStart() override
	{

	}

	void OnUpdate() override
	{

	}

	void OnDraw() override
	{

	}
};

Window* WindowInstance()
{
	return new Sandbox("Oxcart Console", 100, 50, 8);
}