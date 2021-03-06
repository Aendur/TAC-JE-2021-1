#include "Game.h"
#include "TitleState.h"

#include <filesystem>
#include <iostream>
#include <random>

#ifndef UNITTEST
int main (int, char ** argv) {
	try {
		//std::setlocale(LC_ALL, "en_US.UTF-8");
		auto wdir = (std::filesystem::current_path()  / argv[0]).parent_path();
		std::cout << "working directory is " << wdir << std::endl;
		std::filesystem::current_path(wdir);
		
		std::srand(std::random_device()());
		Game & game = Game::GetInstance();
		game.Push(new TitleState());
		game.Run();
		Game::DeleteInstance();
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "main return 0" << std::endl;
	return 0;
}
#endif
