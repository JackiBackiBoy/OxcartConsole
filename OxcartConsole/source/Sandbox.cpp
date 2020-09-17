#include "core/Window.h"
#include "input/Keyboard.h"
#include <iostream>

class Sandbox : public Window
{
public:
	Sandbox(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize)
		: Window::Window(aTitle, aScreenWidth, aScreenHeight, aPixelSize) {};

	void OnStart() override
	{
		//myTexture = new Texture2D("resources/textures/mario.png");
		myTexture = new Texture2D("resources/textures/tilemaps/dungeon_blue.png");
	}

	void OnUpdate(const float& aDeltaTime) override
	{
		// Move left
		if (Keyboard::IsKeyDown(KeyCode::Left))
		{
			myPosition.x -= aDeltaTime * 0.05f;
		}
		// Move right
		if (Keyboard::IsKeyDown(KeyCode::Right))
		{
			myPosition.x += aDeltaTime * 0.05f;
		}
	}

	void OnDraw(const float& aDeltaTime) override
	{
		DrawTexture(*myTexture, myPosition);
	}

private:
	Texture2D* myTexture;
	Vector2D myPosition;
};

Window* WindowInstance()
{
	return new Sandbox("Oxcart Console", 100, 100, 8);
}