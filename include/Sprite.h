#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include "Component.h"

class Sprite : public Component {
private:
	SDL_Texture * texture = nullptr;
	int width = -1;
	int height = -1;
	SDL_Rect clipRect;

public:
	Sprite (GameObject& associated);
	Sprite (GameObject& associated, const std::string & file);
	~Sprite (void);

	void Open (const std::string & file);
	void Reopen (const std::string & file);
	void SetClip (int x, int y, int w, int h);
	int GetWidth (void);
	int GetHeight (void);
	bool IsOpen (void);
	void Render (int x, int y);
	
	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
