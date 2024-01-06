#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int speed = 3;



	TransformComponent(): position({0.0f, 0.0f}), velocity({ 0.0f, 0.0f })
	{ 
	}
	TransformComponent(float x, float y): position({x, y}), velocity({ 0.0f, 0.0f })
	{
	}


	void init() override
	{

	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}


};