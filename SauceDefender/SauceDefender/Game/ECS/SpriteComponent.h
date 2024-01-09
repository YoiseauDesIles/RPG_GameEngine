#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"
#include "../Game.h"

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
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string path)
	{
		setTexture(path);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;
		
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTexture(id);
	}

	~SpriteComponent()
	{
	}

	void setTexture(std::string id)
	{
		texture = Game::assets->GetTexture(id);
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

		srcRect.y = animIndex * transform->height;

		dstRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		dstRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
			
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect, spriteFlip);
	}

	void Play(const char* animationName)
	{
		frames = animations[animationName].frames;
		animIndex = animations[animationName].index;
		speed = animations[animationName].speed;
	}
};