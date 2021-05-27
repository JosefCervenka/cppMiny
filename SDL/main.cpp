#include "SDL.h"
#include "Game.h"

Game* game = NULL;

int main(int argc, char* argv[]) {

	game = new Game();

	const int FPS = 30;
	const int frameDelay = 1000 / FPS;


	Uint32 frameStart;
	int frameTime;


	game->init("Hledani min", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);



	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		game->render();
	}

	game->clean();

	return 0;
}