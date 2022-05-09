#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include "Component.h"
#include "Resources.h"
#include "Timer.h"
#include "Vec2.h"

class Sprite : public Component {
private:
	//SDL_Texture * texture = nullptr;
	SharedTexture texture;
	int width = -1;
	int height = -1;
	SDL_Rect clipRect;
	Vec2 scale;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	Timer selfDestructCount;
	float secondsToSelfDestruct;

public:
	Sprite (GameObject& associated);
	Sprite (GameObject& associated, const std::string & file, int frameCount = 1, float frameTime = 1.0f, float secondsToSelfDestruct = -1.0f);
	~Sprite (void);

	void Open (const std::string & file);
	void Reopen (const std::string & file);
	void SetClip (int x, int y, int w, int h);
	int GetWidth (void);
	int GetHeight (void);
	bool IsOpen (void);
	void Render (int x, int y);

	void SetScale(float scaleX, float scaleY);
	const Vec2 & GetScale(void) const;

	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	
	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
