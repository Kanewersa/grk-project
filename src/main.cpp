#include <iostream>

#include "zombies.h"

int main()
{
	const auto game = new zombies::ZombieGame();
	game->run();

	delete game;
	return 0;
}
