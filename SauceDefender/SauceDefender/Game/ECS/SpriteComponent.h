#pragma once

#include "Components.h"
#include "SDL.h"
#include <string>
#include "../TextureManager.h"

class SpriteComponent : public Component
{

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	bool animated = false;
	int frames = 0;
	//Delay between frames in ms
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const std::string& path)
	{
		setTexture(path);
	}

	SpriteComponent(const std::string& path, int nFrames, int mSpeed)
		:frames(nFrames), speed(mSpeed)
	{
		animated = true;
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const std::string& path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		dstRect.x = static_cast<int>(transform->position.x);
		dstRect.y = static_cast<int>(transform->position.y);

		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
			
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect);
	}

};