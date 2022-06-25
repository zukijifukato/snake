#include "Core.h"

int main(int argc, char* argv[]) {
	Core* game = new Core();

	game->init("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

	// Frame per second implemented on CORE
	
	while(game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	delete game;

	return 0;
}