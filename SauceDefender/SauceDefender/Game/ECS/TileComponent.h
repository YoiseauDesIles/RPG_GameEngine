#pragma once

#include "ECS.h"
#include "SDL.h"


class TileComponent : public Component
{

public:
	
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect, dstRect;

	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xPos, int yPos, std::string path)
		:srcRect({srcX, srcY, 32, 32}), dstRect({xPos, yPos, 64, 64})
	{
		texture = TextureManager::LoadTexture(path);
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}


};
