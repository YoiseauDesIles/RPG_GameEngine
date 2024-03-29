#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;
class AssetManager;

class Game
{

private:
	int cnt = 0;
	SDL_Window* window;
	//SDL_Renderer* renderer;

public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles
	};

};

