#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>

class Sprite {
private:
	SDL_Texture * texture = nullptr;
	int width = -1;
	int height = -1;
	SDL_Rect clipRect;

public:
	Sprite (void);
	Sprite (std::string file);
	~Sprite (void);
	void Open (std::string file);
	void SetClip (int x, int y, int w, int h);
	void Render (int x, int y);
	int GetWidth (void);
	int GetHeight (void);
	bool IsOpen (void);
};

#endif
