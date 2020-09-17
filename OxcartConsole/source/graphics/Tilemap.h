#ifndef TILEMAP_HEADER
#define TILEMAP_HEADER

#include "Texture2D.h"

class Tilemap
{
public:
	Tilemap(Texture2D& aTexture, const int& aTileWidth, const int& aTileHeight);
	~Tilemap();

private:
	Texture2D* myTilemapTexture;
	int myTileWidth;
	int myTileHeight;
};
#endif