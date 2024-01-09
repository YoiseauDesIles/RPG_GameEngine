#include "Game.h"
#include "TextureManager.h"

#include "GameMap.h"

#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"


GameMap* map = nullptr;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

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

		Game::isRunning = true;
	}
	else
	{
		Game::isRunning = false;
	}

	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("player", "Assets/player_anims.png");
	assets->AddTexture("projectile", "Assets/projectile.png");

	map = new GameMap("terrain", 3, 32);

	//ECS implementation
	map->LoadMap("Assets/map.map", 25, 20);
	
	player.addComponent<TransformComponent>(0, 0, 32, 32, 3);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	assets->CreateProjectile(Vector2D(200, 200), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 0), Vector2D(-2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 250), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(260, 260), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(300, 200), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 200), Vector2D(2, 1), 200, 2, "projectile");

	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{

	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	std::string playerTag = player.getComponent<ColliderComponent>().tag;
	Vector2D playerPosition = player.getComponent<TransformComponent>().position;


	manager.refresh();
	manager.update();


	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		std::string currTag = c->getComponent<ColliderComponent>().tag;
		if (Collision::AABB(cCollider, playerCollider) && currTag != playerTag)
		{
			std::cout << c->getComponent<ColliderComponent>().tag << "\n";
			std::cout << c->getComponent<ColliderComponent>().dstRect.x << "\n";
			std::cout << c->getComponent<ColliderComponent>().dstRect.y << "\n";

			std::cout << playerCollider.x << "\n";
			std::cout << playerCollider.y << "\n";
			

			//std::cout << "here\n";
			player.getComponent<TransformComponent>().position = playerPosition;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "hit the player\n";
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;



	/*Vector2D playerVelocity = player.getComponent<TransformComponent>().velocity;
	int playerSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().dstRect.x += -(playerVelocity.x * playerSpeed);
		t->getComponent<TileComponent>().dstRect.y += -(playerVelocity.y * playerSpeed);

	}*/
	
}



void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}
	/*for (auto& e : enemies)
	{
		e->draw();
	}*/


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

