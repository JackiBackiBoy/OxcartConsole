#include "Texture2D.h"
#include "thirdparty/stb_image/stb_image.h"
#include "Color.h"

Texture2D::Texture2D(const std::string& aFilePath)
{
	unsigned char* tempTextureData = stbi_load(aFilePath.c_str(), &myWidth, &myHeight, &myChannelCount, 0);
	myPixelBuffer = new unsigned char[myWidth * myHeight];

	if (tempTextureData != NULL)
	{
		// Get the pixel data from the file
		for (size_t i = myChannelCount - 1; i < myWidth * myHeight * myChannelCount; i += myChannelCount)
		{
			unsigned char tempR = tempTextureData[i - (myChannelCount - 1)];
			unsigned char tempG = tempTextureData[i - (myChannelCount - 2)];
			unsigned char tempB = tempTextureData[i - (myChannelCount - 3)];
			unsigned char tempA = myChannelCount < 4 ? 255 : tempTextureData[i];

			myPixelBuffer[i / myChannelCount] = Color::ToConsoleColor({ tempR, tempG, tempB, tempA });
		}
	}

	stbi_image_free(tempTextureData);
}

Texture2D::~Texture2D()
{
	delete[] myPixelBuffer;
}
