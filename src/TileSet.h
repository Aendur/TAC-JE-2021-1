#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.h"

class TileSet {
private:
	//Sprite tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;

public:
	TileSet (int tileWidth, int tileHeight, const std::string & file);
	void RenderTile(unsigned int index, float x, float y);
	int GetTileWidth(void);
	int GetTileHeight(void);
};

#endif
