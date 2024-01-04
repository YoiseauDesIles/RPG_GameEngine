#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* enemy;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystem initialized" << "\n";
		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << "\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << "\n";

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new GameObject("Assets/player.png", renderer, 0, 0);
	enemy = new GameObject("Assets/enemy.png", renderer, 50, 50);

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	player->update();
	enemy->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	player->render();
	enemy->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "GameCleaned" << "\n";
}

bool Game::running()
{
	return isRunning;
}
