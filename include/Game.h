#ifndef GAME_H
#define GAME_H

#include <string>
#include <stack>
#include <memory>
#include <SDL2/SDL.h>

class State;

class Game {
private:
	int frameStart = 0;
	float dt = -1.0f;
	
	inline static Game * instance = nullptr;
	
	State * storedState = nullptr;
	SDL_Window * window = nullptr;
	SDL_Renderer * renderer = nullptr;
	std::stack<std::unique_ptr<State>> stateStack;
	
	void CalculateDeltaTime(void);
	bool ManageStates(void);
	void StartStoredState(void);
	void PopAndResumeState(void);

	Game(const std::string &, int, int);
public:
	~Game(void);
	
	static Game & GetInstance (void);
	static void DeleteInstance (void);
	SDL_Renderer * GetRenderer (void) const;
	State & GetCurrentState (void) const;
	void Push(State * state);
	void Run(void);
	float GetDeltaTime(void);
};

#endif
