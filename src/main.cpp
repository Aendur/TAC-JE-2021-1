#include "Game.h"
#include <ctime>

int main (int, char ** ) {
	std::srand(std::time(NULL));
	Game game = Game::GetInstance();
	game.Run();
	return 0;
}