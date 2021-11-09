#ifndef GAME_H
#define GAME_H

#include <string>
#include <SDL2/SDL.h>

class State;

class Game {
private:
	inline static Game * instance = nullptr;
	SDL_Window * window = nullptr;
	SDL_Renderer * renderer = nullptr;
	State * state = nullptr;
	
	Game(std::string, int, int);
	
	int frameStart;
	float dt;
	void CalculateDeltaTime(void);

public:
	~Game(void);
	void Run(void);
	SDL_Renderer * GetRenderer (void);
	State & GetState (void);
	static Game & GetInstance (void);

	float GetDeltaTime(void);
};

#endif
