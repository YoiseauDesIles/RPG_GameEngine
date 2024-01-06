#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"


class TileComponent : public Component
{

public:
	TransformComponent* transform = nullptr;
	SpriteComponent* sprite = nullptr;

	SDL_Rect tileRect;
	int tileID;
	std::string path;

	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id) 
		:tileRect({x,y,w,h}), tileID(id)
	{

		switch (tileID)
		{
		case 0:
			path = "Assets/water.png";
			break;
		case 1:
			path = "Assets/dirt.png";
			break;
		case 2:
			path = "Assets/grass.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}

};
