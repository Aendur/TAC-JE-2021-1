#ifndef TILESET_H
#define TILESET_H

#include "Component.h"
#include "Sprite.h"
#include <string>

class TileSet : public Component {
private:
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;

public:
	//TileSet (int tileWidth, int tileHeight, const std::string & file);
	TileSet (GameObject& associated, int tileWidth, int tileHeight, const std::string & file);
	void RenderTile(unsigned int index, float x, float y);
	int GetTileWidth(void);
	int GetTileHeight(void);

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type);
};

#endif
