#include "TileSet.h"
#include "Sprite.h"
#include "errors.h"

//class TileSet {
//private:
//	Sprite tileSet;
//	int rows;
//	int columns;
//	int tileWidth;
//	int tileHeight;
//};

TileSet::TileSet (int tileWidth, int tileHeight, const std::string & file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	(void) file;
	//this->tileSet = Sprite(associated, file);
	throw std::logic_error(MSG_INCOMPLETE_IMPLMT);
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
	(void) index;
	(void) x;
	(void) y;
	std::string msg = std::string(__FILE__) + ": unimplemented | " + std::to_string(__LINE__);
	throw std::logic_error(msg);
}

int TileSet::GetTileWidth(void) {
	return this->tileWidth;
}

int TileSet::GetTileHeight(void) {
	return this->tileHeight;
}
