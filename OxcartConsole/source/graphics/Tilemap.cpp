#include "Tilemap.h"

Tilemap::Tilemap(Texture2D& aTileMapTexture, const int& aTileWidth, const int& aTileHeight)
	: myTilemapTexture(&aTileMapTexture), myTileWidth(aTileWidth), myTileHeight(aTileHeight)
{
}

Tilemap::~Tilemap()
{

}