#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <string>
#include "Windows.h"

class Window
{
public:
	Window(const std::string& aTitle, const int& aScreenWidth, const int& aScreenHeight, const int& aPixelSize);
	~Window();

	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;

	int Run();

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