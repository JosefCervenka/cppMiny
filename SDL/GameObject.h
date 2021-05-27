#pragma once
#include "Game.h"

enum playerMark {
	flag,
	question_mark,
	unknown,
	known,
};

enum fieldType {
	bomb,
	freeSpace,
};

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();

	void UpdateTexture(const char* texturesheet);

	void Render();


	int bombsAround = 0;

	int xpos;
	int ypos;
	SDL_Rect srcRect, destRect;

	fieldType fieldType = freeSpace;
	playerMark playerMark = unknown;

private:
	SDL_Texture* objTexture;
};


