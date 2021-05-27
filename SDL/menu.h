#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "SDL_image.h"
#include <string>


class Menu
{
	public:
	Menu();
	~Menu();

	void init(const char* title, int xpos, int ypos, int width, int height);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	static SDL_Renderer* renderer;


	private:
	bool isRunning;
	SDL_Window* window;
};
