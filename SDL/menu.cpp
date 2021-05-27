#include "Menu.h"
Menu::Menu() {

}
Menu::~Menu() {

}
void Menu::init(const char* title, int xpos, int ypos, int width, int height) {

	int flags = 0;


	if (SDL_Init(SDL_INIT_EVERYTHING) == false) {

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}




void Menu::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:

		int xField = event.motion.x / 32;
		int yField = event.motion.y / 32;

		if (event.button.button == 1) {


		}
		else if (event.button.button == 3)
		{

		}

		break;
	}
}

void Menu::update() {


}

//void Menu::render() {
//
//}

void Menu::clean() {

}
