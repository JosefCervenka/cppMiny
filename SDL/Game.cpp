#include "Game.h"
#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <string>
using namespace std;


const int fieldX = 30;
const int fieldY = 30;

const int bombs = 100;

GameObject* fields[fieldX][fieldY];

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	else {
		flags = 0;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == false) {

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer,0,0,0,255);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	for (int x = 0; x < fieldX; x++)
	{
		for (int y = 0; y < fieldY; y++)
		{
			fields[x][y] = new GameObject("Assets/unknown.png", 32 * x, 32 * y);
		}
	}

	for (int i = 0; i < bombs; i++)
	{
		int xRand = rand() % fieldX;
		int yRand = rand() % fieldY;

		if (fields[xRand][yRand]->fieldType == freeSpace) {
			fields[xRand][yRand]->fieldType = bomb;
		}
		else {
			i--;
		}
	}

	for (int x = 0; x < fieldX; x++)
	{
		for (int y = 0; y < fieldY; y++)
		{
			if (fields[x][y]->fieldType == bomb)
			{
				std::cout << "o";
			}
			else
			{
				if (x - 1 >= 0) {
					if(fields[x-1][y]->fieldType == bomb)
					fields[x][y]->bombsAround++;
				}
				if (x + 1 <= fieldX-1) {
					if (fields[x + 1][y]->fieldType == bomb)
					fields[x][y]->bombsAround++;
				}
				if (y - 1 >= 0) {
					if (fields[x][y-1]->fieldType == bomb)
					fields[x][y]->bombsAround++;
				}
				if (y + 1 <= fieldY-1) {
					if (fields[x][y+1]->fieldType == bomb)
					fields[x][y]->bombsAround++;
				}

				if (y - 1 >= 0 && x - 1 >= 0) {
					if (fields[x - 1][y-1]->fieldType == bomb)
					fields[x][y]->bombsAround++;
				}
				if (y - 1 >= 0 && x + 1 <= fieldX-1) {
					if (fields[x + 1][y-1]->fieldType == bomb)
						fields[x][y]->bombsAround++;
				}
				if (y + 1 <= fieldY-1 && x - 1 >= 0) {
					if (fields[x - 1][y+1]->fieldType == bomb)
						fields[x][y]->bombsAround++;
				}
				if (y + 1 <= fieldY-1 && x + 1 <= fieldX-1) {
					if (fields[x + 1][y+1]->fieldType == bomb)
						fields[x][y]->bombsAround++;
				}




				std::cout << fields[x][y]->bombsAround;
			}
		}

		std::cout << std::endl;
	}
}


void recursiveSearch(int x, int y) {


	if (fields[x][y]->bombsAround == 0) {
		fields[x][y]->UpdateTexture("Assets/space.png");

		fields[x][y]->playerMark = known;

		if ((x - 1 >= 0)){
			if (fields[x-1][y]->playerMark == unknown)
			recursiveSearch(x - 1, y);
		}
		if ((x + 1 < fieldX)) {
			if (fields[x + 1][y]->playerMark == unknown)
			recursiveSearch(x + 1, y);
		}
		if ((y - 1 >= 0)) {
			if (fields[x][y-1]->playerMark == unknown)
			recursiveSearch(x, y - 1);
		}
		if ((y + 1 < fieldY)) {
			if (fields[x][y + 1]->playerMark == unknown)
				recursiveSearch(x, y + 1);
		}




		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			if (fields[x - 1][y - 1]->playerMark == unknown)
				recursiveSearch(x - 1, y - 1);
		}

		if ((x + 1 < fieldX) && (y + 1 < fieldY)) {
			if (fields[x + 1][y + 1]->playerMark == unknown)
				recursiveSearch(x + 1, y + 1);
		}
		if ((x - 1 >= 0) && (y + 1 < fieldY)) {
			if (fields[x - 1][y + 1]->playerMark == unknown)
				recursiveSearch(x - 1, y + 1);
		}
		if ((x + 1 < fieldX) && (y - 1 >= 0)) {
			if (fields[x + 1][y - 1]->playerMark == unknown)
				recursiveSearch(x + 1, y - 1);
		}

		cout << endl;
	}
	else
	{
		fields[x][y]->playerMark = known;
		string Path = "Assets/space" + to_string(fields[x][y]->bombsAround) + ".png";
		fields[x][y]->UpdateTexture(Path.c_str());
	}
}

void Game::handleEvents() {
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

			if ((xField < fieldX) && (yField < fieldY)) {

				if(fields[xField][yField]->playerMark == unknown)
				if (fields[xField][yField]->fieldType == bomb) {

					for (int x = 0; x < fieldX; x++)
					{
						for (int y = 0; y < fieldY; y++)
						{
							//fields[x][y]

							if (fields[x][y]->fieldType == bomb)
							{
								fields[x][y]->UpdateTexture("Assets/bomb.png");
							}
							else {
								fields[x][y]->UpdateTexture("Assets/space.png");
							}
						}
					}

					fields[xField][yField]->UpdateTexture("Assets/explode.png");


				}
				else{

					recursiveSearch(xField, yField);

					//cout << xField << yField << endl;
				}
			}

		}
		else if(event.button.button == 3)
		{
			
			if ((xField < fieldX) && (yField < fieldY)) {
				if (fields[xField][yField]->playerMark == unknown) {
					fields[xField][yField]->playerMark = flag;
					fields[xField][yField]->UpdateTexture("Assets/flag.png");

					
				}
				else if (fields[xField][yField]->playerMark == flag) {
					fields[xField][yField]->playerMark = question_mark;
					fields[xField][yField]->UpdateTexture("Assets/questionmark.png");
				}
				else if (fields[xField][yField]->playerMark == question_mark) {
					fields[xField][yField]->playerMark = unknown;
					fields[xField][yField]->UpdateTexture("Assets/unknown.png");
				}
			}
			
		}

		break;
	}
}

void Game::update() {

	for (int x = 0; x < fieldX; x++)
	{
		for (int y = 0; y < fieldY; y++)
		{
			fields[x][y]->Update();
		}
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (int x = 0; x < fieldX; x++)
	{
		for (int y = 0; y < fieldY; y++)
		{
			fields[x][y]->Render();
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
