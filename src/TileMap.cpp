#include "errors.h"
#include "TileMap.h"
#include <iostream>
#include <fstream>

/*class TileMap : public Component {
private:
	std::vector<int> tileMatrix;
	TileSet * tileSet;
	int mapWidth = -1;
	int mapHeight = -1;
	int mapDepth = -1;
};*/

TileMap::TileMap (GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated) {
	(void) file;
	(void) tileSet;
	this->Load(file);
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

TileMap::~TileMap (void) {
	//throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void TileMap::Load (const std::string & file) {
	(void) file;
	std::ifstream stream(file);
	std::string line;
	while(!stream.eof()) {
		stream >> line;
		std::cout << "LINE " << line << std::endl;
	}
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void TileMap::SetTileSet (TileSet * tileSet) {
	(void) tileSet;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

int& TileMap::At (int x, int y, int z) {
	(void) x;
	(void) y;
	(void) z;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

int TileMap::GetWidth (void) {
	return this->mapWidth;
}

int TileMap::GetHeight (void) {
	return this->mapHeight;
}

int TileMap::GetDepth (void) {
	return this->mapDepth;
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY) {
	(void) layer;
	(void) cameraX;
	(void) cameraY;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

// inherited from component
void TileMap::Update (float dt) {
	(void) dt;
}

void TileMap::Render (void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

bool TileMap::Is (const std::string & type) {
	return (type.compare("TileMap") == 0);
}

#ifdef UNITTEST
#ifdef UNITTEST_TILEMAP
#include "GameObject.h"
int main (int, char ** ) {
	GameObject obj;
	TileMap tm(obj, "bin/assets/map/tileMap.txt", NULL);
	return 0;
}

#endif
#endif