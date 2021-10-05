#include "Game.h"
#include <ctime>

#ifndef UNITTEST
int main (int, char ** ) {
	std::srand(std::time(NULL));
	Game game = Game::GetInstance();
	game.Run();
	return 0;
}
#endif
