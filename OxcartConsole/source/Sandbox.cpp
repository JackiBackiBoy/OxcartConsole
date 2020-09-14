#include "core/Window.h"
#include <iostream>

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize)
		: Window::Window(aTitle, aScreenWidth, aScreenHeight, aPixelSize) {};

	void OnStart() override
	{
		myTexture = new Texture2D("resources/textures/mario.png");
	}

	void OnUpdate(const float& aDeltaTime) override
	{

	}

	void OnDraw(const float& aDeltaTime) override
	{
		DrawTexture(*myTexture, { 0, 0 });
	}

private:
	Texture2D* myTexture;
};

Window* WindowInstance()
{
	return new Sandbox("Oxcart Console | Made by Jack Henrikson", 50, 50, 8);
}