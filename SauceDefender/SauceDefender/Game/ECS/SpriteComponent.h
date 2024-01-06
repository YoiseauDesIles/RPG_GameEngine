#pragma once

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{

private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		dstRect.x = dstRect.y = 0;
		dstRect.w = dstRect.h = 64;
	}

	void update() override
	{
		dstRect.x = position->x();
		dstRect.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect);
	}

};