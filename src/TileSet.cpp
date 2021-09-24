#include "TileSet.h"
#include <stdexcept>

//class TileSet {
//private:
//	Sprite tileSet;
//	int rows;
//	int columns;
//	int tileWidth;
//	int tileHeight;
//
//public:
//	TileSet (int tileWidth, int tileHeight, const std::string & file);
//	void RenderTile(unsigned int index, float x, float y);
//	int GetTileWidth();
//	int GetTileHeight();
//};

TileSet::TileSet (int tileWidth, int tileHeight, const std::string & file) {
	(void) tileWidth;
	(void) tileHeight;
	(void) file;
	std::string msg = std::string(__FILE__) + ": unimplemented | " + std::to_string(__LINE__);
	throw std::logic_error(msg);
	// this->tileWidth = tileWidth;
	// this->tileHeight = tileHeight;
	// this->tileSet = 
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
