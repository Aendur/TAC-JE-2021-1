#include "TileSet.h"
#include "errors.h"

//class TileSet {
//private:
//	Sprite tileSet;
//	int rows;
//	int columns;
//	int tileWidth;
//	int tileHeight;
//};

TileSet::TileSet (GameObject& associated, int tileWidth, int tileHeight, const std::string & file) : Component(associated), tileSet(associated, file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->rows = tileSet.GetHeight() / tileHeight;
	this->columns = tileSet.GetWidth() / tileWidth;
}

#include <iostream>
void TileSet::RenderTile (int index, float x, float y) {
	if (index < 0) {
	} else if (index < tileWidth * tileHeight) {
		int col = index % columns;
		int row = (index - col) / columns;
		int x0 = col * tileWidth;
		int y0 = row * tileHeight;
		tileSet.SetClip(x0, y0, tileWidth, tileHeight);
		tileSet.Render((int)x, (int)y);
	} else {
		throw std::out_of_range("tile index out of bounds");
	}
}

int TileSet::GetTileWidth(void) {
	return this->tileWidth;
}

int TileSet::GetTileHeight(void) {
	return this->tileHeight;
}

// Inherited from Component
void TileSet::Update(float dt) { (void) dt; }

void TileSet::Render (void) { }

bool TileSet::Is (const std::string & type) const {
	return type.compare("TileSet") == 0;
}

const std::string TileSet::GetType(void) const {
	return "TileSet";
}
