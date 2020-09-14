#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <string>
#include "Windows.h"
#include <graphics/Texture2D.h>
#include <math/Vector2D.h>

class Window
{
public:
	Window(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize);
	~Window();

	virtual void OnStart() = 0;
	virtual void OnUpdate(const float& aDeltaTime) = 0;
	virtual void OnDraw(const float& aDeltaTime) = 0;

	void DrawTexture(Texture2D& aTexture, const Vector2D& aPosition);

	void Run();

private:
	HANDLE myInputHandle;
	HANDLE myOutputHandle;
	CHAR_INFO* myScreenBuffer;

protected:
	std::string myTitle;
	int myScreenWidth;
	int myScreenHeight;
	int myPixelSize;
};
#endif