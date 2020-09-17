#include "Window.h"
#include <chrono>
#include <algorithm>

Window::Window(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize)
	: myTitle(aTitle), myScreenWidth(aScreenWidth), myScreenHeight(aScreenHeight), myPixelSize(aPixelSize)
{
	myInputHandle = GetStdHandle(STD_INPUT_HANDLE);
	myOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CHAR_INFO tempCharInfo;
	tempCharInfo.Attributes = 0;
	tempCharInfo.Char.UnicodeChar = 0x0020;

	myScreenBuffer = new CHAR_INFO[myScreenWidth * myScreenHeight] { tempCharInfo };

}

Window::~Window()
{
	delete[] myScreenBuffer;
}

void Window::OnStart()
{
	// Set font size, i.e. The size of each character or "pixel"
	CONSOLE_FONT_INFOEX tempCFI;
	tempCFI.cbSize = sizeof(tempCFI);
	tempCFI.nFont = 0;
	tempCFI.dwFontSize.X = myPixelSize;
	tempCFI.dwFontSize.Y = myPixelSize;
	tempCFI.FontFamily = FF_DONTCARE;
	tempCFI.FontWeight = FW_NORMAL;
	wcscpy_s(tempCFI.FaceName, L"Terminal"); // wide-char-string copy

	if (SetCurrentConsoleFontEx(myOutputHandle, false, &tempCFI))
	{
		int a = 0;
	}

	DWORD tempErrorCFI = GetLastError();

	// Temporarily set the console window width and height to 1 to allow
	// the screen buffer size to be set without any issues
	SMALL_RECT tempWindowRectangle = { 0, 0, 1, 1 };
	if (SetConsoleWindowInfo(myOutputHandle, TRUE, &tempWindowRectangle))
	{
	}

	// Set the width and height of the screen buffer (in characters)
	if (SetConsoleScreenBufferSize(myOutputHandle, { (short)myScreenWidth, (short)myScreenHeight }))
	{
	}

	// Set the width and height of the console window (in characters
	tempWindowRectangle = { 0, 0, (short)myScreenWidth - 1, (short)myScreenHeight - 1 };
	if (SetConsoleWindowInfo(myOutputHandle, TRUE, &tempWindowRectangle))
	{
	}

	// Change the 16 console colors to be more vibrant
	CONSOLE_SCREEN_BUFFER_INFOEX tempCSBI;
	tempCSBI.cbSize = sizeof(tempCSBI);

	if (GetConsoleScreenBufferInfoEx(myOutputHandle, &tempCSBI))
	{
		tempCSBI.ColorTable[0] = RGB(0, 0, 0);
		tempCSBI.ColorTable[1] = RGB(0, 0, 128);
		tempCSBI.ColorTable[2] = RGB(0, 128, 0);
		tempCSBI.ColorTable[3] = RGB(0, 128, 128);
		tempCSBI.ColorTable[4] = RGB(128, 0, 0);
		tempCSBI.ColorTable[5] = RGB(128, 0, 128);
		tempCSBI.ColorTable[6] = RGB(128, 128, 0);
		tempCSBI.ColorTable[7] = RGB(170, 170, 170);
		tempCSBI.ColorTable[8] = RGB(85, 85, 85);
		tempCSBI.ColorTable[9] = RGB(0, 0, 255);
		tempCSBI.ColorTable[10] = RGB(0, 255, 0);
		tempCSBI.ColorTable[11] = RGB(0, 255, 255);
		tempCSBI.ColorTable[12] = RGB(255, 0, 0);
		tempCSBI.ColorTable[13] = RGB(255, 0, 255);
		tempCSBI.ColorTable[14] = RGB(255, 255, 0);
		tempCSBI.ColorTable[15] = RGB(255, 255, 255);

		++tempCSBI.srWindow.Right;
		++tempCSBI.srWindow.Bottom;

		SetConsoleScreenBufferInfoEx(myOutputHandle, &tempCSBI);
	}

	// Disable further functionality in the console window like quick-edit, insert-mode, etc.
	// This allows the console to only act as a raw window where the functionality is instead
	// guided by the engine and not the console.
	unsigned long tempConsoleMode;

	if (GetConsoleMode(myInputHandle, &tempConsoleMode))
	{
		// Disables all mouse input, quick-edit, control shortcuts, etc.
		tempConsoleMode = 0x0008 | 0x0010 | 0x0080;

		SetConsoleMode(myInputHandle, tempConsoleMode);
	}

	// Hide the blinking console cursor
	CONSOLE_CURSOR_INFO tempCCI;

	if (GetConsoleCursorInfo(myOutputHandle, &tempCCI))
	{
		tempCCI.bVisible = false;
		SetConsoleCursorInfo(myOutputHandle, &tempCCI);
	}

	DWORD tempError = GetLastError();
}

void Window::OnUpdate(const float& aDeltaTime)
{
	// Set the title of console to include the title of program and stats about the window
	std::wstring tempTitle = std::wstring(myTitle.begin(), myTitle.end()) + L" | " +  std::to_wstring(aDeltaTime) + L" ms";
	SetConsoleTitleW(tempTitle.c_str());
}

void Window::OnDraw(const float& aDeltaTime)
{
	SMALL_RECT tempWindowRectangle = { 0, 0, (short)myScreenWidth - 1, (short)myScreenHeight - 1 };
	WriteConsoleOutputW(myOutputHandle, myScreenBuffer, { (short)myScreenWidth, (short)myScreenHeight }, { 0, 0 }, &tempWindowRectangle);

	CHAR_INFO tempCharInfo;
	tempCharInfo.Attributes = 0;
	tempCharInfo.Char.UnicodeChar = 0x0020;
	std::fill(myScreenBuffer, myScreenBuffer + myScreenWidth * myScreenHeight, tempCharInfo);
}

void Window::DrawTexture(Texture2D& aTexture, const Vector2D& aPosition)
{
	int tempTextureWidth = aTexture.GetWidth();
	int tempTextureHeight = aTexture.GetHeight();
	unsigned char* tempPixelData = aTexture.GetPixelBuffer();

	for (size_t i = 0; i < tempTextureWidth * tempTextureHeight; i++)
	{
		// 0x00FF (essentially the 17th color) indicates that the color should be transparent, thus not needed to be drawn to the buffer
		if (tempPixelData[i] != 0x00FF)
		{
			// Check that the pixel to be drawn isn't outside the screen
			if (aPosition.x + i % tempTextureWidth >= 0 && aPosition.x + i % tempTextureWidth < myScreenWidth &&
				aPosition.y + (i / tempTextureWidth) >= 0 && aPosition.y + (i / tempTextureWidth) < myScreenHeight)
			{
				int tempIndex = myScreenWidth * (i / tempTextureWidth + aPosition.y) + aPosition.x + i % tempTextureWidth;

				myScreenBuffer[tempIndex].Attributes = tempPixelData[i];
				myScreenBuffer[tempIndex].Char.UnicodeChar = 0x0020;
			}
		}
	}
}

void Window::Run()
{
	Window::OnStart();
	OnStart();

	float tempDeltaTime = 0.0f;

	// Game loop
	while (true)
	{
		auto tempStartTime = std::chrono::high_resolution_clock::now();

		OnUpdate(tempDeltaTime);
		Window::OnUpdate(tempDeltaTime);

		OnDraw(tempDeltaTime);
		Window::OnDraw(tempDeltaTime);

		auto tempEndTime = std::chrono::high_resolution_clock::now();
		tempDeltaTime = std::chrono::duration<float, std::milli>(tempEndTime - tempStartTime).count();
	}
}