#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{

public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex = nullptr;
	SDL_Rect srcRect, dstRect;
	TransformComponent* transform = nullptr;

	ColliderComponent(std::string t)
		: tag(t), collider({0, 0, 0, 0}), srcRect({0, 0, 32, 32}), dstRect({0, 0, 32, 32})
	{
	}

	ColliderComponent(std::string tag, int xPos, int yPos, int size)
		: tag(tag), collider({ xPos, yPos, size, size }), srcRect({ 0, 0, 32, 32 }), dstRect({ 0, 0, 32, 32 })
	{
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/colTex.png");
		dstRect = { collider.x, collider.y, collider.w, collider.h };

	}

	void update() override
	{

		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
		
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcRect, dstRect, SDL_FLIP_NONE);
	}
};
