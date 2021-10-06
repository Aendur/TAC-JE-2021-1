#include "errors.h"
#include "TileMap.h"
#include "GameObject.h"
#include "TileSet.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*class TileMap : public Component {
private:
	std::vector<int> tileMatrix;
	TileSet * tileSet;
	int mapWidth = -1;
	int mapHeight = -1;
	int mapDepth = -1;
};*/

TileMap::TileMap (GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated) {
	this->Load(file);
	this->SetTileSet(tileSet);
}

TileMap::~TileMap (void) { }

void TileMap::Load (const std::string & file) {
	std::ifstream stream(file);

	std::string sWidth, sHeight, sDepth;
	std::getline(stream, sWidth, ',');
	std::getline(stream, sHeight, ',');
	std::getline(stream, sDepth, ',');
	this->mapWidth = stoi(sWidth);
	this->mapHeight = stoi(sHeight);
	this->mapDepth = stoi(sDepth);

	std::string sValue;
	while(!stream.eof()) {
		std::getline(stream, sValue, ',');
		try {
			int value = stoi(sValue) - 1;
			tileMatrix.push_back(value);
			//std::cout << sValue.length() << " LINE={" << sValue << "} VAL " << value << std::endl;
		} catch (std::invalid_argument & e) {
			std::cout << "warning, invalid argument on function " << __FUNCTION__ << ": " << e.what() << std::endl;
		}
	}

	long long expected = ((long long) mapWidth) * mapHeight * mapDepth;
	long long current = (long long) tileMatrix.size();
	if (current != expected) {
		throw std::runtime_error(file + " missing indices (expected: " + std::to_string(expected) + " got: " + std::to_string(current) + ")");
	}
}

void TileMap::SetTileSet (TileSet * tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At (int x, int y, int z) {
	int index = z * this->mapWidth * this->mapHeight + y * this->mapWidth + x;
	return this->tileMatrix.at(index);
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
	int w = tileSet->GetTileWidth();
	int h = tileSet->GetTileHeight();
	for(int y = 0; y < mapHeight; ++y) {
		for(int x = 0; x < mapWidth; ++x) {
			int index = At(x, y, layer);
			float xpos = cameraX + x * w;
			float ypos = cameraY + y * h;
			tileSet->RenderTile(index, xpos, ypos);
		}
	}
}

// inherited from component
void TileMap::Update (float dt) {
	(void) dt;
}

void TileMap::Render (void) {
	for (int layer = 0; layer < this->mapDepth; ++layer) {
		this->RenderLayer (layer, 0.0, 0.0);
	}
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