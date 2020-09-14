#ifndef TEXTURE_2D_HEADER
#define TEXTURE_2D_HEADER

#include <string>

class Texture2D
{
public:
	Texture2D(const std::string& aFilePath);
	~Texture2D();

	inline int GetWidth() const { return myWidth; }
	inline int GetHeight() const { return myHeight; }
	inline unsigned char* GetPixelBuffer() const { return myPixelBuffer; }

private:
	int myWidth;
	int myHeight;
	int myChannelCount;
	unsigned char* myPixelBuffer;
};
#endif