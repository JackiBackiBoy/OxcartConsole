#include "Window.h"

Window::Window(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize)
	: myTitle(aTitle), myScreenWidth(aScreenWidth), myScreenHeight(aScreenHeight), myPixelSize(aPixelSize)
{
	myInputHandle = GetStdHandle(STD_INPUT_HANDLE);
	myOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	myScreenBuffer = new CHAR_INFO[myScreenWidth * myScreenHeight];
}

Window::~Window()
{
	delete myScreenBuffer;
}

void Window::OnStart()
{
	SetConsoleScreenBufferSize(myOutputHandle, { (short)myScreenWidth - 1, (short)myScreenHeight - 1 });

	SMALL_RECT tempWindowRectangle = { 0, 0, (short)myScreenWidth - 1, (short)myScreenHeight - 1 };
	SetConsoleWindowInfo(myOutputHandle, TRUE, &tempWindowRectangle);
}

void Window::OnUpdate()
{

}

void Window::OnDraw()
{

}

int Window::Run()
{
	OnStart();
	Window::OnStart();

	while (true)
	{
		OnUpdate();
		Window::OnUpdate();

		OnDraw();
		Window::OnDraw();
	}
}