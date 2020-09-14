#include "Color.h"
#include "Windows.h"
#include <string>

Color::~Color()
{

}

unsigned char Color::ToConsoleColor(const Color& aColor)
{
	if (aColor.a == 255)
	{
		CONSOLE_SCREEN_BUFFER_INFOEX tempCSBI;
		tempCSBI.cbSize = sizeof(tempCSBI);

		// Get current colors in the color table of the console
		GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &tempCSBI);

		// Distance to RGB color (3d space)
		double tempNearestColorDistance = DBL_MAX;
		int tempNearestColorIndex;

		for (size_t i = 0; i < 16; i++)
		{
			// Pythagoras
			int tempRDifference = (int)GetRValue(tempCSBI.ColorTable[i]) - aColor.r;
			int tempGDifference = (int)GetGValue(tempCSBI.ColorTable[i]) - aColor.g;
			int tempBDifference = (int)GetBValue(tempCSBI.ColorTable[i]) - aColor.b;

			double tempDistance = sqrtf(tempRDifference * tempRDifference + tempGDifference * tempGDifference + tempBDifference * tempBDifference);
			//double tempDistance = abs(GetRValue(tempCSBI.ColorTable[i]) - myRed) + abs(GetGValue(tempCSBI.ColorTable[i]) - myGreen) + abs(GetBValue(tempCSBI.ColorTable[i]) - myBlue);

			if (tempDistance < tempNearestColorDistance)
			{
				tempNearestColorDistance = tempDistance;
				tempNearestColorIndex = i;
			}
		}

		return (tempNearestColorIndex * 16); // multiplying by sixteen to use 8-bit format
	}

	return 0x00FF; // indicates that the color is transparent and shouldn't be shown on the screen (17th color)
}