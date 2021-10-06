#include "Game.h"

#include <ctime>
#include <filesystem>
#include <iostream>

#ifndef UNITTEST
int main (int, char ** argv) {
	auto wdir = (std::filesystem::current_path()  / argv[0]).parent_path();
	std::cout << "working directory is " << wdir << std::endl;
	std::filesystem::current_path(wdir);
	
	std::srand(std::time(NULL));
	Game game = Game::GetInstance();
	game.Run();

	return 0;
}
#endif
