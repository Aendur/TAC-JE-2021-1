#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>

#include "Component.h"

class TileSet;

class TileMap : public Component {
private:
	std::vector<int> tileMatrix;
	TileSet * tileSet;
	int mapWidth = -1;
	int mapHeight = -1;
	int mapDepth = -1;

public:
	TileMap (GameObject& associated, const std::string& file, TileSet* tileSet);
	~TileMap (void);

	void Load (const std::string & file);
	void SetTileSet (TileSet * tileSet);
	int & At (int x, int y, int z = 0);
	
	int GetWidth (void);
	int GetHeight (void);
	int GetDepth (void);
	
	void RenderLayer (int layer, int cameraX, int cameraY);

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
