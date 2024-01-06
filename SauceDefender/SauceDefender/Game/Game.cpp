#include "Game.h"
#include "TextureManager.h"

#include "GameMap.h"

#include "ECS/Components.h"


GameMap* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

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

	map = new GameMap();

	
	//ECS implementation
	player.addComponent<PositionComponent>(0, 0);
	player.addComponent<SpriteComponent>("Assets/player.png");

	
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

	manager.refresh();
	manager.update();

	if (player.getComponent<PositionComponent>().x() > 100)
	{
		player.getComponent<SpriteComponent>().setTexture("Assets/enemy.png");
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	manager.draw();

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
