#ifndef COLOR_HEADER
#define COLOR_HEADER

struct Color
{
	Color() : r(0), g(0), b(0), a(255) {};
	Color(const int& aRed, const int& aGreen, const int& aBlue, const int& anAlpha = 255) : r(aRed), g(aGreen), b(aBlue), a(anAlpha) {};
	~Color();

	static unsigned char ToConsoleColor(const Color& aColor);

	int r;
	int g;
	int b;
	int a;
};
#endif