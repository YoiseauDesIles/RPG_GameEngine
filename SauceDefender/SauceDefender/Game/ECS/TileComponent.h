#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"

class TileComponent : public Component
{

public:
	
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect, dstRect;
	Vector2D position;

	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xPos, int yPos, int tsize, int tscale, std::string id)
		:srcRect({srcX, srcY, tsize, tsize }), dstRect({xPos, yPos, tsize * tscale, tsize  * tscale}), position({ (float)xPos, (float)yPos})
	{
		texture = Game::assets->GetTexture(id);
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}


	void update() override
	{
		dstRect.x = position.x - Game::camera.x;
		dstRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}


};
